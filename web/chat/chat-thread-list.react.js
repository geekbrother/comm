// @flow

import invariant from 'invariant';
import * as React from 'react';

import { searchUsers as searchUserCall } from 'lib/actions/user-actions.js';
import useChatThreadList from 'lib/hooks/use-chat-thread-list';
import {
  type ChatThreadItem,
  useFlattenedChatListData,
} from 'lib/selectors/chat-selectors.js';
import { threadSearchIndex as threadSearchIndexSelector } from 'lib/selectors/nav-selectors';
import { usersWithPersonalThreadSelector } from 'lib/selectors/user-selectors.js';
import {
  emptyItemText,
  threadInBackgroundChatList,
  threadInHomeChatList,
} from 'lib/shared/thread-utils';
import { threadTypes } from 'lib/types/thread-types';
import { useServerCall } from 'lib/utils/action-utils.js';

import { useSelector } from '../redux/redux-utils';
import { activeChatThreadItem as activeChatThreadItemSelector } from '../selectors/chat-selectors';
import ChatThreadListItem from './chat-thread-list-item.react';
import Search from './chat-thread-list-search.react';
import css from './chat-thread-list.css';
import { ThreadListContext } from './thread-list-provider';

type Props = {
  +setModal: (modal: ?React.Node) => void,
};

function ChatThreadList(props: Props): React.Node {
  const { setModal } = props;
  const threadListContext = React.useContext(ThreadListContext);
  invariant(
    threadListContext,
    'threadListContext should be set in ChatThreadList',
  );
  const { activeTab } = threadListContext;
  const boundChatListData = useFlattenedChatListData();
  const viewerID = useSelector(
    state => state.currentUserInfo && state.currentUserInfo.id,
  );
  const threadSearchIndex = useSelector(threadSearchIndexSelector);
  const callSearchUsers = useServerCall(searchUserCall);
  const usersWithPersonalThread = useSelector(usersWithPersonalThreadSelector);

  const isBackground = activeTab === 'Background';

  const [searchText, setSearchText] = React.useState('');
  const [threadSearchResults, setThreadSearchResults] = React.useState(
    new Set(),
  );
  const [usersSearchResults, setUsersSearchResults] = React.useState([]);

  const activeChatThreadItem = useSelector(activeChatThreadItemSelector);

  const makeSureActiveSidebarIsIncluded = React.useCallback(
    (threadListData: $ReadOnlyArray<ChatThreadItem>) => {
      if (
        !activeChatThreadItem ||
        activeChatThreadItem.threadInfo.type !== threadTypes.SIDEBAR
      ) {
        return threadListData;
      }

      const sidebarParentIndex = threadListData.findIndex(
        thread =>
          thread.threadInfo.id ===
          activeChatThreadItem.threadInfo.parentThreadID,
      );
      if (sidebarParentIndex === -1) {
        return threadListData;
      }
      const parentItem = threadListData[sidebarParentIndex];

      for (const sidebarItem of parentItem.sidebars) {
        if (sidebarItem.type !== 'sidebar') {
          continue;
        } else if (
          sidebarItem.threadInfo.id === activeChatThreadItem.threadInfo.id
        ) {
          return threadListData;
        }
      }

      let indexToInsert = parentItem.sidebars.findIndex(
        sidebar =>
          sidebar.lastUpdatedTime === undefined ||
          sidebar.lastUpdatedTime < activeChatThreadItem.lastUpdatedTime,
      );
      if (indexToInsert === -1) {
        indexToInsert = parentItem.sidebars.length;
      }
      const activeSidebar = {
        type: 'sidebar',
        lastUpdatedTime: activeChatThreadItem.lastUpdatedTime,
        mostRecentNonLocalMessage:
          activeChatThreadItem.mostRecentNonLocalMessage,
        threadInfo: activeChatThreadItem.threadInfo,
      };
      const newSidebarItems = [...parentItem.sidebars];
      newSidebarItems.splice(indexToInsert, 0, activeSidebar);

      const newThreadListData = [...threadListData];
      newThreadListData[sidebarParentIndex] = {
        ...parentItem,
        sidebars: newSidebarItems,
      };
      return newThreadListData;
    },
    [activeChatThreadItem],
  );

  const searchUsers = React.useCallback(
    async (usernamePrefix: string) => {
      if (usernamePrefix.length === 0) {
        return [];
      }

      const { userInfos } = await callSearchUsers(usernamePrefix);
      return userInfos.filter(
        info => !usersWithPersonalThread.has(info.id) && info.id !== viewerID,
      );
    },
    [callSearchUsers, usersWithPersonalThread, viewerID],
  );

  React.useEffect(() => {
    (async () => {
      const results = threadSearchIndex.getSearchResults(searchText);
      setThreadSearchResults(new Set(results));
      setUsersSearchResults(await searchUsers(searchText));
    })();
  }, [searchText, boundChatListData, threadSearchIndex, searchUsers]);

  const threadFilter = React.useMemo(
    () => (isBackground ? threadInBackgroundChatList : threadInHomeChatList),
    [isBackground],
  );

  const chatListDataWithoutFilter = useChatThreadList(
    boundChatListData,
    searchText,
    threadFilter,
    threadSearchResults,
    usersSearchResults,
    viewerID,
  );
  const listData = React.useMemo(
    () => makeSureActiveSidebarIsIncluded(chatListDataWithoutFilter),
    [chatListDataWithoutFilter, makeSureActiveSidebarIsIncluded],
  );

  const threadComponents: React.Node[] = React.useMemo(() => {
    const threads = listData.map(item => (
      <ChatThreadListItem
        item={item}
        key={item.threadInfo.id}
        setModal={setModal}
      />
    ));
    if (threads.length === 0 && isBackground) {
      threads.push(<EmptyItem key="emptyItem" />);
    }
    return threads;
  }, [listData, isBackground, setModal]);

  return (
    <div className={css.threadListContainer}>
      <Search onChangeText={setSearchText} searchText={searchText} />
      <div>{threadComponents}</div>
    </div>
  );
}

function EmptyItem() {
  return <div className={css.emptyItem}>{emptyItemText}</div>;
}

export default ChatThreadList;
