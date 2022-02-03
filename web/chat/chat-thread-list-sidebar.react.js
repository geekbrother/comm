// @flow

import classNames from 'classnames';
import * as React from 'react';

import type { SidebarInfo } from 'lib/types/thread-types';

import { useThreadIsActive } from '../selectors/nav-selectors';
import css from './chat-thread-list.css';
import SidebarItem from './sidebar-item.react';

type Props = {
  +sidebarInfo: SidebarInfo,
};
function ChatThreadListSidebar(props: Props): React.Node {
  const { sidebarInfo } = props;
  const { threadInfo } = sidebarInfo;
  const threadID = threadInfo.id;
  const active = useThreadIsActive(threadID);
  const activeStyle = active ? css.activeThread : null;
  return (
    <div
      className={classNames(css.threadListSideBar, css.sidebar, activeStyle)}
    >
      <SidebarItem sidebarInfo={sidebarInfo} />
    </div>
  );
}

export default ChatThreadListSidebar;
