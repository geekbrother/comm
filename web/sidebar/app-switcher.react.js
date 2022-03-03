// @flow

import invariant from 'invariant';
import * as React from 'react';
import { useDispatch } from 'react-redux';

import {
  mostRecentReadThreadSelector,
  unreadCount,
} from 'lib/selectors/thread-selectors';

import { useSelector } from '../redux/redux-utils';
import SWMansionIcon from '../SWMansionIcon.react';
import { updateNavInfoActionType } from '../types/nav-types';
import css from './left-layout-aside.css';
import NavigationPanel from './navigation-panel.react';

function AppSwitcher(): React.Node {
  const activeChatThreadID = useSelector(
    state => state.navInfo.activeChatThreadID,
  );
  const mostRecentReadThread = useSelector(mostRecentReadThreadSelector);
  const activeThreadCurrentlyUnread = useSelector(
    state =>
      !activeChatThreadID ||
      !!state.threadStore.threadInfos[activeChatThreadID]?.currentUser.unread,
  );
  const viewerID = useSelector(
    state => state.currentUserInfo && state.currentUserInfo.id,
  );

  const dispatch = useDispatch();

  const onClickCalendar = React.useCallback(
    (event: SyntheticEvent<HTMLAnchorElement>) => {
      event.preventDefault();
      dispatch({
        type: updateNavInfoActionType,
        payload: { tab: 'calendar' },
      });
    },
    [dispatch],
  );

  const onClickChat = React.useCallback(
    (event: SyntheticEvent<HTMLAnchorElement>) => {
      event.preventDefault();
      dispatch({
        type: updateNavInfoActionType,
        payload: {
          tab: 'chat',
          activeChatThreadID: activeThreadCurrentlyUnread
            ? mostRecentReadThread
            : activeChatThreadID,
        },
      });
    },
    [
      dispatch,
      activeThreadCurrentlyUnread,
      mostRecentReadThread,
      activeChatThreadID,
    ],
  );

  const boundUnreadCount = useSelector(unreadCount);

  invariant(viewerID, 'should be set');
  let chatBadge = null;
  if (boundUnreadCount > 0) {
    chatBadge = <div className={css.chatBadge}>{boundUnreadCount}</div>;
  }

  const chatNavigationItem = React.useMemo(
    () => (
      <p>
        <span className={css.chatIconWrapper}>
          <SWMansionIcon icon="message-square" size={24} />
          {chatBadge}
        </span>
        <a onClick={onClickChat}>Chat</a>
      </p>
    ),
    [chatBadge, onClickChat],
  );

  const calendarNavigationItem = React.useMemo(
    () => (
      <p>
        <SWMansionIcon icon="calendar" size={24} />
        <a onClick={onClickCalendar}>Calendar</a>
      </p>
    ),
    [onClickCalendar],
  );

  const navigationItems = React.useMemo(
    () => [
      { tab: 'chat', link: chatNavigationItem },
      {
        tab: 'calendar',
        link: calendarNavigationItem,
      },
    ],
    [calendarNavigationItem, chatNavigationItem],
  );

  return <NavigationPanel navigationItems={navigationItems} />;
}

export default AppSwitcher;
