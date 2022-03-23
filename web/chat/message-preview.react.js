// @flow

import classNames from 'classnames';
import * as React from 'react';

import { getMessageTitle } from 'lib/shared/message-utils';
import { threadIsGroupChat } from 'lib/shared/thread-utils';
import { stringForUser } from 'lib/shared/user-utils';
import {
  type MessageInfo,
  messageTypes,
  type ComposableMessageInfo,
  type RobotextMessageInfo,
} from 'lib/types/message-types';
import { type ThreadInfo } from 'lib/types/thread-types';

import { getDefaultTextMessageRules } from '../markdown/rules.react';
import css from './chat-thread-list.css';

type Props = {
  +messageInfo: ?MessageInfo,
  +threadInfo: ThreadInfo,
};
function MessagePreview(props: Props): React.Node {
  const { messageInfo: messageInfoProps, threadInfo } = props;
  const { unread } = threadInfo.currentUser;

  const colorStyle = unread ? css.white : css.light;

  if (!messageInfoProps) {
    return (
      <div className={classNames(css.lastMessage, css.dark, css.italic)}>
        No messages
      </div>
    );
  }
  const messageInfo: ComposableMessageInfo | RobotextMessageInfo =
    messageInfoProps.type === messageTypes.SIDEBAR_SOURCE
      ? messageInfoProps.sourceMessage
      : messageInfoProps;

  const messageTitle = getMessageTitle(
    messageInfo,
    threadInfo,
    getDefaultTextMessageRules().simpleMarkdownRules,
  );
  if (messageInfo.type === messageTypes.TEXT) {
    let usernameText = null;
    if (
      threadIsGroupChat(threadInfo) ||
      threadInfo.name !== '' ||
      messageInfo.creator.isViewer
    ) {
      const userString = stringForUser(messageInfo.creator);
      const username = `${userString}: `;
      usernameText = <span className={colorStyle}>{username}</span>;
    }
    return (
      <div className={classNames(css.lastMessage, colorStyle)}>
        {usernameText}
        {messageTitle}
      </div>
    );
  } else {
    return (
      <div className={classNames([css.lastMessage, colorStyle])}>
        {messageTitle}
      </div>
    );
  }
}

export default MessagePreview;
