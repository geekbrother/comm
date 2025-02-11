// @flow

import invariant from 'invariant';
import * as React from 'react';

import { unreadBackgroundCount } from 'lib/selectors/thread-selectors';

import Tabs from '../components/tabs.react';
import { useSelector } from '../redux/redux-utils';
import css from './chat-tabs.css';
import ChatThreadList from './chat-thread-list.react';
import ChatThreadTab from './chat-thread-tab.react';
import { ThreadListContext } from './thread-list-provider';

function ChatTabs(): React.Node {
  let backgroundTitle = 'Background';
  const unreadBackgroundCountVal = useSelector(unreadBackgroundCount);
  if (unreadBackgroundCountVal) {
    backgroundTitle += ` (${unreadBackgroundCountVal})`;
  }
  const threadListContext = React.useContext(ThreadListContext);
  invariant(
    threadListContext,
    'threadListContext should be set in ChatThreadList',
  );
  const { activeTab, setActiveTab } = threadListContext;

  const setActiveChatTab = React.useCallback(
    (newTab: 'Background' | 'Focus') => {
      setActiveTab(newTab);
    },
    [setActiveTab],
  );

  const chatThreadList = React.useMemo(
    () => (
      <div className={css.threadList}>
        <ChatThreadList />
      </div>
    ),
    [],
  );

  const focusTabsItem = React.useMemo(
    () => (
      <Tabs.Item
        id="Focus"
        header={<ChatThreadTab title="Focus" icon="message-filled-round" />}
      >
        {chatThreadList}
      </Tabs.Item>
    ),
    [chatThreadList],
  );

  const backgroundTabsItem = React.useMemo(
    () => (
      <Tabs.Item
        id="Background"
        header={<ChatThreadTab title={backgroundTitle} icon="bell-disabled" />}
      >
        {chatThreadList}
      </Tabs.Item>
    ),
    [backgroundTitle, chatThreadList],
  );

  return (
    <div className={css.container}>
      <Tabs.Container activeTab={activeTab} setTab={setActiveChatTab}>
        {focusTabsItem}
        {backgroundTabsItem}
      </Tabs.Container>
    </div>
  );
}

export default ChatTabs;
