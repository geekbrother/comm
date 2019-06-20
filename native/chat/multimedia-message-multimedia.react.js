// @flow

import { type MediaInfo, mediaInfoPropType } from 'lib/types/media-types';
import type { ImageStyle } from '../types/styles';
import {
  type Navigate,
  MultimediaModalRouteName,
} from '../navigation/route-names';
import {
  type VerticalBounds,
  verticalBoundsPropType,
} from '../types/lightbox-types';
import {
  type PendingMultimediaUpload,
  pendingMultimediaUploadPropType,
} from './chat-input-state';
import type { TooltipItemData } from '../components/tooltip.react';

import * as React from 'react';
import PropTypes from 'prop-types';
import { View, StyleSheet } from 'react-native';
import Animated from 'react-native-reanimated';
import * as Progress from 'react-native-progress';
import Icon from 'react-native-vector-icons/Feather';
import { KeyboardUtils } from 'react-native-keyboard-input';
import invariant from 'invariant';

import Multimedia from '../media/multimedia.react';
import Tooltip from '../components/tooltip.react';
import { saveImage } from '../media/save-image';

type Props = {|
  mediaInfo: MediaInfo,
  navigate: Navigate,
  verticalBounds: ?VerticalBounds,
  style?: ImageStyle,
  modalsClosed: bool,
  lightboxPosition: ?Animated.Value,
  inProgress: bool,
  pendingUpload: ?PendingMultimediaUpload,
  keyboardShowing: bool,
  messageFocused: bool,
  toggleMessageFocus: (messageKey: string) => void,
  setScrollDisabled: (scrollDisabled: bool) => void,
|};
type State = {|
  hidden: bool,
  opacity: ?Animated.Value,
|};
class MultimediaMessageMultimedia extends React.PureComponent<Props, State> {

  static propTypes = {
    mediaInfo: mediaInfoPropType.isRequired,
    navigate: PropTypes.func.isRequired,
    verticalBounds: verticalBoundsPropType,
    modalsClosed: PropTypes.bool.isRequired,
    lightboxPosition: PropTypes.instanceOf(Animated.Value),
    inProgress: PropTypes.bool.isRequired,
    pendingUpload: pendingMultimediaUploadPropType,
    keyboardShowing: PropTypes.bool.isRequired,
    messageFocused: PropTypes.bool.isRequired,
    toggleMessageFocus: PropTypes.func.isRequired,
    setScrollDisabled: PropTypes.func.isRequired,
  };
  view: ?View;
  tooltipConfig: $ReadOnlyArray<TooltipItemData>;
  tooltip: ?Tooltip;

  constructor(props: Props) {
    super(props);
    this.state = {
      hidden: false,
      opacity: this.getOpacity(),
    };
    this.tooltipConfig = [
      { label: "Save", onPress: this.onPressSave },
    ];
  }

  static getDerivedStateFromProps(props: Props, state: State) {
    if (props.modalsClosed && state.hidden) {
      return { hidden: false };
    }
    return null;
  }

  getOpacity() {
    const { lightboxPosition } = this.props;
    if (!lightboxPosition) {
      return null;
    }
    return Animated.interpolate(
      this.props.lightboxPosition,
      {
        inputRange: [ 0.1, 0.11 ],
        outputRange: [ 1, 0 ],
        extrapolate: Animated.Extrapolate.CLAMP,
      },
    );
  }

  componentDidUpdate(prevProps: Props) {
    const { lightboxPosition } = this.props;
    if (lightboxPosition !== prevProps.lightboxPosition) {
      this.setState({ opacity: this.getOpacity() });
    }
  }

  render() {
    const { mediaInfo, pendingUpload, style, inProgress } = this.props;

    let failed = mediaInfo.id.startsWith('localUpload') && !inProgress;
    let progressPercent = 1;
    if (pendingUpload) {
      ({ progressPercent, failed } = pendingUpload);
    }

    let progressIndicator;
    if (failed) {
      progressIndicator = (
        <View style={styles.centerContainer}>
          <Icon
            name="alert-circle"
            style={styles.uploadError}
            size={64}
          />
        </View>
      );
    } else if (progressPercent !== 1) {
      progressIndicator = (
        <View style={styles.centerContainer}>
          <Progress.Circle
            size={100}
            indeterminate={progressPercent === 0}
            progress={progressPercent}
            borderWidth={5}
            fill="#DDDDDD"
            unfilledColor="#DDDDDD"
            color="#88BB88"
            thickness={15}
            showsText={true}
            textStyle={styles.progressIndicatorText}
          />
        </View>
      );
    }

    const wrapperStyles = [ styles.expand ];
    if (this.state.hidden && this.state.opacity) {
      wrapperStyles.push({ opacity: this.state.opacity });
    }

    const multimedia = (
      <View style={[ styles.multimediaContainer, style ]} ref={this.viewRef}>
        <Animated.View style={wrapperStyles}>
          <Multimedia mediaInfo={mediaInfo} />
          {progressIndicator}
        </Animated.View>
      </View>
    );

    return (
      <Tooltip
        buttonComponent={multimedia}
        items={this.tooltipConfig}
        componentWrapperStyle={styles.expand}
        componentContainerStyle={styles.expand}
        labelStyle={styles.popoverLabelStyle}
        onOpenTooltipMenu={this.onFocus}
        onCloseTooltipMenu={this.onBlur}
        onPressOverride={this.onPress}
        onLongPress={this.onLongPress}
        innerRef={this.tooltipRef}
      />
    );
  }

  viewRef = (view: ?View) => {
    this.view = view;
  }

  tooltipRef = (tooltip: ?Tooltip) => {
    this.tooltip = tooltip;
  }

  onPress = () => {
    const { view, props: { verticalBounds }, tooltip } = this;
    if (!view || !verticalBounds) {
      return;
    }
    if (tooltip) {
      tooltip.hideModal();
    }
    view.measure((x, y, width, height, pageX, pageY) => {
      const coordinates = { x: pageX, y: pageY, width, height };
      const { mediaInfo, navigate } = this.props;
      navigate({
        routeName: MultimediaModalRouteName,
        params: { mediaInfo, initialCoordinates: coordinates, verticalBounds },
      });
      this.setState({ hidden: true });
    });
  }

  onFocus = () => {
    this.props.setScrollDisabled(true);
    if (!this.props.messageFocused) {
      this.props.toggleMessageFocus(this.props.mediaInfo.messageKey);
    }
  }

  onBlur = () => {
    this.props.setScrollDisabled(false);
    if (this.props.messageFocused) {
      this.props.toggleMessageFocus(this.props.mediaInfo.messageKey);
    }
  }

  onPressSave = () => {
    return saveImage(this.props.mediaInfo);
  }

  onLongPress = () => {
    if (this.props.keyboardShowing) {
      KeyboardUtils.dismiss();
      return;
    }
    const tooltip = this.tooltip;
    invariant(tooltip, "tooltip should be set");
    if (this.props.messageFocused) {
      tooltip.hideModal();
    } else {
      tooltip.openModal();
    }
  }

}

const styles = StyleSheet.create({
  multimediaContainer: {
    flex: 1,
    overflow: 'hidden',
  },
  expand: {
    flex: 1,
  },
  centerContainer: {
    position: 'absolute',
    top: 0,
    bottom: 0,
    left: 0,
    right: 0,
    alignItems: 'center',
    justifyContent: 'center',
  },
  progressIndicatorText: {
    color: 'black',
    fontSize: 21,
  },
  uploadError: {
    color: "white",
    textShadowColor: "#000",
    textShadowOffset: { width: 0, height: 1 },
    textShadowRadius: 1,
  },
  popoverLabelStyle: {
    textAlign: 'center',
    color: '#444',
  },
});

export default MultimediaMessageMultimedia;
