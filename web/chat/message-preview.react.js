// @flow

import classNames from 'classnames';
import * as React from 'react';

import { useMessagePreview } from 'lib/hooks/message-preview';
import { type MessageInfo } from 'lib/types/message-types';
import { type ThreadInfo } from 'lib/types/thread-types';

import { getDefaultTextMessageRules } from '../markdown/rules.react';
import css from './chat-thread-list.css';

type Props = {
  +messageInfo: ?MessageInfo,
  +threadInfo: ThreadInfo,
};
function MessagePreview(props: Props): React.Node {
  const {
    messageInfo: originalMessageInfo,
    threadInfo,
    threadInfo: {
      currentUser: { unread },
    },
  } = props;

  const { message: messageTitle, username } = useMessagePreview(
    originalMessageInfo,
    threadInfo,
    getDefaultTextMessageRules().simpleMarkdownRules,
  );

  const colorStyle = unread ? css.unread : css.read;
  if (!originalMessageInfo) {
    return (
      <div className={classNames(css.lastMessage, css.dark, css.italic)}>
        No messages
      </div>
    );
  }

  let usernameText = null;
  if (username) {
    usernameText = <span className={colorStyle}>{`${username}: `}</span>;
  }

  return (
    <div className={classNames(css.lastMessage, colorStyle)}>
      {usernameText}
      {messageTitle}
    </div>
  );
}

export default MessagePreview;
