// @flow

import invariant from 'invariant';
import * as React from 'react';

import { threadInfoSelector } from 'lib/selectors/thread-selectors';
import { threadInChatList } from 'lib/shared/thread-utils';
import { threadTypes } from 'lib/types/thread-types';

import { useSelector } from '../redux/redux-utils';
import { activeChatThreadItem as activeChatThreadItemSelector } from '../selectors/chat-selectors';

type ChatTabType = 'Focused' | 'Background';
type ThreadListContextType = {
  +activeTab: ChatTabType,
  +setActiveTab: (newActiveTab: ChatTabType) => void,
};

const ThreadListContext: React.Context<?ThreadListContextType> = React.createContext<?ThreadListContextType>();

type ThreadListProviderProps = {
  +children: React.Node,
};
function ThreadListProvider(props: ThreadListProviderProps): React.Node {
  const [activeTab, setActiveTab] = React.useState('Focused');

  const activeChatThreadItem = useSelector(activeChatThreadItemSelector);
  const activeThreadInfo = activeChatThreadItem?.threadInfo;
  const activeThreadID = activeThreadInfo?.id;

  const activeSidebarParentThreadInfo = useSelector(state => {
    if (!activeThreadInfo || activeThreadInfo.type !== threadTypes.SIDEBAR) {
      return null;
    }
    const { parentThreadID } = activeThreadInfo;
    invariant(parentThreadID, 'sidebar must have parent thread');
    return threadInfoSelector(state)[parentThreadID];
  });
  const activeTopLevelThreadInfo =
    activeThreadInfo?.type === threadTypes.SIDEBAR
      ? activeSidebarParentThreadInfo
      : activeThreadInfo;

  const activeTopLevelThreadIsFromHomeTab =
    activeTopLevelThreadInfo?.currentUser.subscription.home;

  const activeTopLevelThreadIsFromDifferentTab =
    (activeTab === 'Focused' && activeTopLevelThreadIsFromHomeTab) ||
    (activeTab === 'Background' && !activeTopLevelThreadIsFromHomeTab);

  const activeTopLevelThreadIsInChatList = React.useMemo(
    () => threadInChatList(activeTopLevelThreadInfo),
    [activeTopLevelThreadInfo],
  );

  const shouldChangeTab =
    activeTopLevelThreadIsInChatList && activeTopLevelThreadIsFromDifferentTab;

  const prevActiveThreadIDRef = React.useRef<?string>();
  React.useEffect(() => {
    const prevActiveThreadID = prevActiveThreadIDRef.current;
    prevActiveThreadIDRef.current = activeThreadID;
    if (activeThreadID !== prevActiveThreadID && shouldChangeTab) {
      setActiveTab(
        activeTopLevelThreadIsFromHomeTab ? 'Focused' : 'Background',
      );
    }
  }, [activeThreadID, shouldChangeTab, activeTopLevelThreadIsFromHomeTab]);

  const threadListContext = React.useMemo(
    () => ({
      activeTab,
      setActiveTab,
    }),
    [activeTab],
  );

  return (
    <ThreadListContext.Provider value={threadListContext}>
      {props.children}
    </ThreadListContext.Provider>
  );
}

export { ThreadListProvider, ThreadListContext };
