// @flow

import classNames from 'classnames';
import invariant from 'invariant';
import * as React from 'react';
import { useDispatch } from 'react-redux';

import {
  mostRecentReadThreadSelector,
  unreadCount,
} from 'lib/selectors/thread-selectors';

import { useSelector } from '../redux/redux-utils';
import SWMansionIcon from '../SWMansionIcon.react';
import getTitle from '../title/getTitle';
import { updateNavInfoActionType } from '../types/nav-types';
import css from './left-layout-aside.css';

function AppSwitcher(): React.Node {
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
  const isCalendarEnabled = useSelector(state => state.enabledApps.calendar);

  React.useEffect(() => {
    document.title = getTitle(boundUnreadCount);
  }, [boundUnreadCount]);

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

  const onClickApps = React.useCallback(
    (event: SyntheticEvent<HTMLAnchorElement>) => {
      event.preventDefault();
      dispatch({
        type: updateNavInfoActionType,
        payload: {
          tab: 'apps',
        },
      });
    },
    [dispatch],
  );

  invariant(viewerID, 'should be set');
  let chatBadge = null;
  if (boundUnreadCount > 0) {
    chatBadge = <div className={css.chatBadge}>{boundUnreadCount}</div>;
  }

  const chatNavClasses = classNames({
    [css.appTab]: true,
    [css.activeTab]: navInfo.tab === 'chat',
  });
  const appsNavClasses = classNames({
    [css.appTab]: true,
    [css.activeTab]: navInfo.tab === 'apps',
  });

  const calendarLink = React.useMemo(() => {
    if (!isCalendarEnabled) {
      return null;
    }
    const calendarNavClasses = classNames({
      [css.appTab]: true,
      [css.activeTab]: navInfo.tab === 'calendar',
    });
    return (
      <div onClick={onClickCalendar} className={calendarNavClasses}>
        <SWMansionIcon icon="calendar" size={24} />
        <p>Calendar</p>
      </div>
    );
  }, [isCalendarEnabled, navInfo.tab, onClickCalendar]);

  return (
    <div className={css.appSwitcherContainer}>
      <div onClick={onClickChat} className={chatNavClasses}>
        <span className={css.chatIconWrapper}>
          <SWMansionIcon icon="message-square" size={24} />
          {chatBadge}
        </span>
        <p>Chat</p>
      </div>
      {calendarLink}
      <div onClick={onClickApps} className={appsNavClasses}>
        <SWMansionIcon icon="wrench" size={24} />
        <p>Apps</p>
      </div>
    </div>
  );
}

export default AppSwitcher;
