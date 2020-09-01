// @flow

import type { InnerLogInPanel, LogInState } from './log-in-panel.react';
import {
  type StateContainer,
  stateContainerPropType,
} from '../utils/state-container';
import type { AppState } from '../redux/redux-setup';

import * as React from 'react';
import { View, Text, StyleSheet } from 'react-native';
import Icon from 'react-native-vector-icons/FontAwesome';
import invariant from 'invariant';
import PropTypes from 'prop-types';
import Animated from 'react-native-reanimated';

import sleep from 'lib/utils/sleep';
import { connect } from 'lib/utils/redux-utils';

import LogInPanel from './log-in-panel.react';
import ForgotPasswordPanel from './forgot-password-panel.react';
import { runTiming } from '../utils/animation-utils';

type LogInMode = 'log-in' | 'forgot-password' | 'forgot-password-success';

/* eslint-disable import/no-named-as-default-member */
const {
  Value,
  Clock,
  block,
  set,
  call,
  cond,
  eq,
  neq,
  lessThan,
  modulo,
  stopClock,
  interpolate,
} = Animated;
/* eslint-enable import/no-named-as-default-member */

type Props = {|
  setActiveAlert: (activeAlert: boolean) => void,
  opacityValue: Value,
  hideForgotPasswordLink: Value,
  logInState: StateContainer<LogInState>,
  innerRef: (container: ?LogInPanelContainer) => void,
  // Redux state
  windowWidth: number,
|};
type State = {|
  logInMode: LogInMode,
  nextLogInMode: LogInMode,
|};
class LogInPanelContainer extends React.PureComponent<Props, State> {
  static propTypes = {
    setActiveAlert: PropTypes.func.isRequired,
    opacityValue: PropTypes.object.isRequired,
    hideForgotPasswordLink: PropTypes.instanceOf(Value).isRequired,
    logInState: stateContainerPropType.isRequired,
    innerRef: PropTypes.func.isRequired,
    windowWidth: PropTypes.number.isRequired,
  };
  logInPanel: ?InnerLogInPanel = null;

  panelTransitionTarget: Value;
  panelTransitionValue: Value;

  constructor(props: Props) {
    super(props);
    this.state = {
      logInMode: 'log-in',
      nextLogInMode: 'log-in',
    };
    this.panelTransitionTarget = new Value(
      LogInPanelContainer.getModeNumber('log-in'),
    );
    this.panelTransitionValue = this.panelTransition();
  }

  proceedToNextMode = () => {
    this.setState({ logInMode: this.state.nextLogInMode });
  };

  static getModeNumber(mode: LogInMode) {
    if (mode === 'log-in') {
      return 0;
    } else if (mode === 'forgot-password') {
      return 1;
    } else if (mode === 'forgot-password-success') {
      return 2;
    }
    invariant(false, `${mode} is not a valid LogInModalMode`);
  }

  panelTransition() {
    const panelTransition = new Value(-1);
    const prevPanelTransitionTarget = new Value(-1);
    const clock = new Clock();
    return block([
      cond(lessThan(panelTransition, 0), [
        set(panelTransition, this.panelTransitionTarget),
        set(prevPanelTransitionTarget, this.panelTransitionTarget),
      ]),
      cond(neq(this.panelTransitionTarget, prevPanelTransitionTarget), [
        stopClock(clock),
        set(prevPanelTransitionTarget, this.panelTransitionTarget),
      ]),
      cond(
        neq(panelTransition, this.panelTransitionTarget),
        set(
          panelTransition,
          runTiming(clock, panelTransition, this.panelTransitionTarget),
        ),
      ),
      cond(eq(modulo(panelTransition, 1), 0), call([], this.proceedToNextMode)),
      panelTransition,
    ]);
  }

  componentDidMount() {
    this.props.innerRef(this);
  }

  componentWillUnmount() {
    this.props.innerRef(null);
  }

  render() {
    const { windowWidth } = this.props;
    const logInPanelDynamicStyle = {
      left: interpolate(this.panelTransitionValue, {
        inputRange: [0, 2],
        outputRange: [0, windowWidth * -2],
      }),
      right: interpolate(this.panelTransitionValue, {
        inputRange: [0, 2],
        outputRange: [0, windowWidth * 2],
      }),
    };
    const logInPanel = (
      <Animated.View style={[styles.panel, logInPanelDynamicStyle]}>
        <LogInPanel
          setActiveAlert={this.props.setActiveAlert}
          opacityValue={this.props.opacityValue}
          innerRef={this.logInPanelRef}
          state={this.props.logInState}
        />
      </Animated.View>
    );
    let forgotPasswordPanel = null;
    if (
      this.state.nextLogInMode !== 'log-in' ||
      this.state.logInMode !== 'log-in'
    ) {
      const forgotPasswordPanelDynamicStyle = {
        left: interpolate(this.panelTransitionValue, {
          inputRange: [0, 2],
          outputRange: [windowWidth, windowWidth * -1],
        }),
        right: interpolate(this.panelTransitionValue, {
          inputRange: [0, 2],
          outputRange: [windowWidth * -1, windowWidth],
        }),
      };
      forgotPasswordPanel = (
        <Animated.View style={[styles.panel, forgotPasswordPanelDynamicStyle]}>
          <ForgotPasswordPanel
            setActiveAlert={this.props.setActiveAlert}
            opacityValue={this.props.opacityValue}
            onSuccess={this.onForgotPasswordSuccess}
          />
        </Animated.View>
      );
    }
    let forgotPasswordSuccess = null;
    if (
      this.state.nextLogInMode === 'forgot-password-success' ||
      this.state.logInMode === 'forgot-password-success'
    ) {
      const forgotPasswordSuccessDynamicStyle = {
        left: interpolate(this.panelTransitionValue, {
          inputRange: [0, 2],
          outputRange: [windowWidth * 2, 0],
        }),
        right: interpolate(this.panelTransitionValue, {
          inputRange: [0, 2],
          outputRange: [windowWidth * -2, 0],
        }),
      };
      const successText =
        "Okay, we've sent that account an email. Check your inbox to " +
        'complete the process.';
      forgotPasswordSuccess = (
        <Animated.View
          style={[styles.panel, forgotPasswordSuccessDynamicStyle]}
        >
          <Icon
            name="check-circle"
            size={48}
            color="#88FF88DD"
            style={styles.forgotPasswordSuccessIcon}
          />
          <Text style={styles.forgotPasswordSuccessText}>{successText}</Text>
        </Animated.View>
      );
    }
    return (
      <View>
        {logInPanel}
        {forgotPasswordPanel}
        {forgotPasswordSuccess}
      </View>
    );
  }

  logInPanelRef = (logInPanel: ?InnerLogInPanel) => {
    this.logInPanel = logInPanel;
  };

  onPressForgotPassword = () => {
    this.props.hideForgotPasswordLink.setValue(1);
    this.setState({ nextLogInMode: 'forgot-password' });
    this.panelTransitionTarget.setValue(
      LogInPanelContainer.getModeNumber('forgot-password'),
    );
  };

  backFromLogInMode = () => {
    if (this.state.nextLogInMode === 'log-in') {
      return false;
    }

    this.setState({
      logInMode: this.state.nextLogInMode,
      nextLogInMode: 'log-in',
    });
    invariant(this.logInPanel, 'ref should be set');
    this.logInPanel.focusUsernameOrEmailInput();

    this.props.hideForgotPasswordLink.setValue(0);
    this.panelTransitionTarget.setValue(
      LogInPanelContainer.getModeNumber('log-in'),
    );

    return true;
  };

  onForgotPasswordSuccess = () => {
    if (this.state.nextLogInMode === 'log-in') {
      return;
    }

    this.setState({ nextLogInMode: 'forgot-password-success' });
    this.panelTransitionTarget.setValue(
      LogInPanelContainer.getModeNumber('forgot-password-success'),
    );

    this.inCoupleSecondsNavigateToLogIn();
  };

  async inCoupleSecondsNavigateToLogIn() {
    await sleep(2350);
    this.backFromLogInMode();
  }
}

const styles = StyleSheet.create({
  forgotPasswordSuccessIcon: {
    marginTop: 40,
    textAlign: 'center',
  },
  forgotPasswordSuccessText: {
    color: 'white',
    fontSize: 18,
    marginLeft: 20,
    marginRight: 20,
    marginTop: 10,
    textAlign: 'center',
  },
  panel: {
    left: 0,
    position: 'absolute',
    right: 0,
  },
});

export default connect((state: AppState) => ({
  windowWidth: state.dimensions.width,
}))(LogInPanelContainer);
