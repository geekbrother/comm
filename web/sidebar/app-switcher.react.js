// @flow

import invariant from 'invariant';
import * as React from 'react';
import { useDispatch } from 'react-redux';

import {
  mostRecentReadThreadSelector,
  unreadCount,
} from 'lib/selectors/thread-selectors';
import type { Dispatch } from 'lib/types/redux-types';

import { useSelector } from '../redux/redux-utils';
import getTitle from '../title/getTitle';
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
  +viewerID: ?string,
  +unreadCount: number,
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
    const { viewerID, unreadCount: curUnreadCount } = this.props;
    invariant(viewerID, 'should be set');
    let chatBadge = null;
    if (curUnreadCount > 0) {
      chatBadge = <div className={css.chatBadge}>{curUnreadCount}</div>;
    }

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
              {chatBadge}
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
    const viewerID = useSelector(
      state => state.currentUserInfo && state.currentUserInfo.id,
    );

    const boundUnreadCount = useSelector(unreadCount);

    const dispatch = useDispatch();

    React.useEffect(() => {
      document.title = getTitle(boundUnreadCount);
    }, [boundUnreadCount]);

    return (
      <AppSwitcher
        navInfo={navInfo}
        dispatch={dispatch}
        mostRecentReadThread={mostRecentReadThread}
        activeThreadCurrentlyUnread={activeThreadCurrentlyUnread}
        viewerID={viewerID}
        unreadCount={boundUnreadCount}
      />
    );
  },
);

export default ConnectedAppSwitcher;
