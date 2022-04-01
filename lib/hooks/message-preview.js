// @flow

import type { ParserRules } from '../shared/markdown';
import { getMessageTitle } from '../shared/message-utils';
import { threadIsGroupChat } from '../shared/thread-utils';
import { stringForUser } from '../shared/user-utils';
import type {
  ComposableMessageInfo,
  MessageInfo,
  RobotextMessageInfo,
} from '../types/message-types';
import { messageTypes } from '../types/message-types';
import type { ThreadInfo } from '../types/thread-types';

type UseMessagePreviewResult = {
  +message: string,
  +username: ?string,
};

function useMessagePreview(
  originalMessageInfo: ?MessageInfo,
  threadInfo: ThreadInfo,
  markdownRules: ParserRules,
): UseMessagePreviewResult {
  if (!originalMessageInfo) {
    return { message: '', username: null };
  }

  const messageInfo: ComposableMessageInfo | RobotextMessageInfo =
    originalMessageInfo.type === messageTypes.SIDEBAR_SOURCE
      ? originalMessageInfo.sourceMessage
      : originalMessageInfo;

  const messageTitle = getMessageTitle(messageInfo, threadInfo, markdownRules);

  const hasUsername =
    threadIsGroupChat(threadInfo) ||
    threadInfo.name !== '' ||
    messageInfo.creator.isViewer;

  let userString = null;
  if (messageInfo.type === messageTypes.TEXT && hasUsername) {
    userString = stringForUser(messageInfo.creator);
  }

  return { message: messageTitle, username: userString };
}

export { useMessagePreview };
