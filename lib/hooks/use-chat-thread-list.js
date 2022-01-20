// @flow

import type { ChatThreadItem } from '../selectors/chat-selectors';
import {
  createPendingThreadItem,
  threadIsTopLevel,
} from '../shared/thread-utils';
import { threadTypes, type ThreadInfo } from '../types/thread-types';
import { type GlobalAccountUserInfo } from '../types/user-types';

function useChatThreadList(
  chatListData: $ReadOnlyArray<ChatThreadItem>,
  searchText: string,
  threadFilter: ThreadInfo => boolean,
  threadSearchResults: Set<string>,
  usersSearchResults: $ReadOnlyArray<GlobalAccountUserInfo>,
  viewerID: ?string,
): $ReadOnlyArray<ChatThreadItem> {
  const chatItems = [];
  if (!searchText) {
    chatItems.push(
      ...chatListData.filter(
        item =>
          threadIsTopLevel(item.threadInfo) && threadFilter(item.threadInfo),
      ),
    );
  } else {
    const privateThreads = [];
    const personalThreads = [];
    const otherThreads = [];
    for (const item of chatListData) {
      if (!threadSearchResults.has(item.threadInfo.id)) {
        continue;
      }
      if (item.threadInfo.type === threadTypes.PRIVATE) {
        privateThreads.push({ ...item, sidebars: [] });
      } else if (item.threadInfo.type === threadTypes.PERSONAL) {
        personalThreads.push({ ...item, sidebars: [] });
      } else {
        otherThreads.push({ ...item, sidebars: [] });
      }
    }
    chatItems.push(...privateThreads, ...personalThreads, ...otherThreads);
    if (viewerID) {
      chatItems.push(
        ...usersSearchResults.map(user =>
          createPendingThreadItem(viewerID, user),
        ),
      );
    }
  }
  return chatItems;
}

export default useChatThreadList;
