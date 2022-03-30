// @flow

import { Entypo } from '@expo/vector-icons';
import * as React from 'react';
import { View, Switch, TouchableOpacity } from 'react-native';
import Alert from 'react-native/Libraries/Alert/Alert';
import Linking from 'react-native/Libraries/Linking/Linking';

import {
  updateSubscriptionActionTypes,
  updateSubscription,
} from 'lib/actions/user-actions';
import type {
  SubscriptionUpdateRequest,
  SubscriptionUpdateResult,
} from 'lib/types/subscription-types';
import { type ThreadInfo } from 'lib/types/thread-types';
import type { DispatchActionPromise } from 'lib/utils/action-utils';
import {
  useServerCall,
  useDispatchActionPromise,
} from 'lib/utils/action-utils';

import { SingleLine } from '../../components/single-line.react';
import { useSelector } from '../../redux/redux-utils';
import { useStyles } from '../../themes/colors';

type BaseProps = {
  +threadInfo: ThreadInfo,
};
type Props = {
  ...BaseProps,
  // Redux state
  +styles: typeof unboundStyles,
  // Redux dispatch functions
  +dispatchActionPromise: DispatchActionPromise,
  // async functions that hit server APIs
  +deviceToken: ?string,
  +updateSubscription: (
    subscriptionUpdate: SubscriptionUpdateRequest,
  ) => Promise<SubscriptionUpdateResult>,
};
type State = {
  +currentValue: boolean,
};
class ThreadSettingsPushNotifs extends React.PureComponent<Props, State> {
  constructor(props: Props) {
    super(props);
    this.state = {
      currentValue: props.threadInfo.currentUser.subscription.pushNotifs,
    };
  }

  render() {
    const componentLabel = 'Push notifs';
    const renderNotificationsSettingsLinkingIcon = () => {
      if (!this.hasPushPermissions()) {
        return (
          <TouchableOpacity
            onPress={this.onNotificationsSettingsLinkingIconPress}
          >
            <View style={this.props.styles.infoIcon}>
              <Entypo name="info-with-circle" size={25} color="gray" />
            </View>
          </TouchableOpacity>
        );
      }
    };
    return (
      <View style={this.props.styles.row}>
        <SingleLine style={this.props.styles.label} adjustsFontSizeToFit={true}>
          {componentLabel}
        </SingleLine>
        {renderNotificationsSettingsLinkingIcon()}
        <View style={this.props.styles.currentValue}>
          <Switch
            value={this.state.currentValue}
            onValueChange={this.onValueChange}
            disabled={!this.hasPushPermissions()}
          />
        </View>
      </View>
    );
  }

  onValueChange = (value: boolean) => {
    this.setState({ currentValue: value });
    this.props.dispatchActionPromise(
      updateSubscriptionActionTypes,
      this.props.updateSubscription({
        threadID: this.props.threadInfo.id,
        updatedFields: {
          pushNotifs: value,
        },
      }),
    );
  };

  onNotificationsSettingsLinkingIconPress = () => {
    Alert.alert(
      'Need notif permissions',
      'Comm needs notification permissions to keep you in the loop! ' +
        'Please enable in Settings App -> Notifications -> Comm.',
      [
        {
          text: 'Go to application settings',
          onPress: () => Linking.openSettings(),
        },
        {
          text: 'Cancel',
          style: 'cancel',
        },
      ],
    );
  };

  hasPushPermissions(): boolean {
    return this.props.deviceToken !== null;
  }
}

const unboundStyles = {
  currentValue: {
    alignItems: 'flex-end',
    margin: 0,
    paddingLeft: 4,
    paddingRight: 0,
    paddingVertical: 0,
  },
  label: {
    color: 'panelForegroundTertiaryLabel',
    fontSize: 16,
    flex: 1,
  },
  row: {
    alignItems: 'center',
    backgroundColor: 'panelForeground',
    flexDirection: 'row',
    paddingHorizontal: 24,
    paddingVertical: 3,
  },
  infoIcon: {
    paddingRight: 20,
  },
};

const ConnectedThreadSettingsPushNotifs: React.ComponentType<BaseProps> = React.memo<BaseProps>(
  function ConnectedThreadSettingsPushNotifs(props: BaseProps) {
    const styles = useStyles(unboundStyles);
    const dispatchActionPromise = useDispatchActionPromise();
    const callUpdateSubscription = useServerCall(updateSubscription);
    const deviceToken = useSelector(state => state.deviceToken);
    return (
      <ThreadSettingsPushNotifs
        {...props}
        styles={styles}
        dispatchActionPromise={dispatchActionPromise}
        updateSubscription={callUpdateSubscription}
        deviceToken={deviceToken}
      />
    );
  },
);

export default ConnectedThreadSettingsPushNotifs;
