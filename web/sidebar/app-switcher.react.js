// @flow

import * as React from 'react';
import { useDispatch } from 'react-redux';

import { mostRecentReadThreadSelector } from 'lib/selectors/thread-selectors';
import type { Dispatch } from 'lib/types/redux-types';

import { useSelector } from '../redux/redux-utils';
import { type NavInfo, updateNavInfoActionType } from '../types/nav-types';
import css from './sidebar.css';

type BaseProps = {};

type Props = {
  // Redux State
  +navInfo: NavInfo,
  // Redux dispatch functions
  +dispatch: Dispatch,
  +mostRecentReadThread: ?string,
  +activeThreadCurrentlyUnread: boolean,
};

class AppSwitcher extends React.PureComponent<Props> {
  onClickCalendar = (event: SyntheticEvent<HTMLAnchorElement>) => {
    event.preventDefault();
    this.props.dispatch({
      type: updateNavInfoActionType,
      payload: { tab: 'calendar' },
    });
  };

  onClickChat = (event: SyntheticEvent<HTMLAnchorElement>) => {
    event.preventDefault();
    this.props.dispatch({
      type: updateNavInfoActionType,
      payload: {
        tab: 'chat',
        activeChatThreadID: this.props.activeThreadCurrentlyUnread
          ? this.props.mostRecentReadThread
          : this.props.navInfo.activeChatThreadID,
      },
    });
  };

  render() {
    return (
      <div className={css.container}>
        <ul>
          <li>
            <p>
              <a onClick={this.onClickCalendar}>Calendar</a>
            </p>
          </li>
          <li>
            <p>
              <a onClick={this.onClickChat}>Chat</a>
            </p>
          </li>
        </ul>
      </div>
    );
  }
}

const ConnectedAppSwitcher: React.ComponentType<BaseProps> = React.memo<BaseProps>(
  function ConnectedAppSwitcher() {
    const activeChatThreadID = useSelector(
      state => state.navInfo.activeChatThreadID,
    );
    const navInfo = useSelector(state => state.navInfo);

    const mostRecentReadThread = useSelector(mostRecentReadThreadSelector);
    const activeThreadCurrentlyUnread = useSelector(
      state =>
        !activeChatThreadID ||
        !!state.threadStore.threadInfos[activeChatThreadID]?.currentUser.unread,
    );

    const dispatch = useDispatch();

    return (
      <AppSwitcher
        navInfo={navInfo}
        dispatch={dispatch}
        mostRecentReadThread={mostRecentReadThread}
        activeThreadCurrentlyUnread={activeThreadCurrentlyUnread}
      />
    );
  },
);

export default ConnectedAppSwitcher;
