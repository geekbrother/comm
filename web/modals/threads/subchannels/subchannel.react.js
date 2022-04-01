// @flow

import * as React from 'react';

import { useMessagePreview } from 'lib/hooks/message-preview';
import { type ChatThreadItem } from 'lib/selectors/chat-selectors';
import { shortAbsoluteDate } from 'lib/utils/date-utils';

import { getDefaultTextMessageRules } from '../../../markdown/rules.react';
import { useSelector } from '../../../redux/redux-utils';
import { useOnClickThread } from '../../../selectors/nav-selectors';
import SWMansionIcon from '../../../SWMansionIcon.react';
import { useModalContext } from '../../modal-provider.react';
import css from './subchannels-modal.css';

type Props = {
  chatThreadItem: ChatThreadItem,
};

function Subchannel(props: Props): React.Node {
  const { chatThreadItem } = props;
  const {
    threadInfo,
    mostRecentMessageInfo,
    lastUpdatedTimeIncludingSidebars,
  } = chatThreadItem;

  const timeZone = useSelector(state => state.timeZone);
  const { clearModal } = useModalContext();

  const navigateToThread = useOnClickThread(threadInfo);

  const onClickThread = React.useCallback(
    event => {
      clearModal();
      navigateToThread(event);
    },
    [clearModal, navigateToThread],
  );

  const lastActivity = React.useMemo(
    () => shortAbsoluteDate(lastUpdatedTimeIncludingSidebars, timeZone),
    [lastUpdatedTimeIncludingSidebars, timeZone],
  );
  const { message, username } = useMessagePreview(
    mostRecentMessageInfo,
    threadInfo,
    getDefaultTextMessageRules().simpleMarkdownRules,
  );

  const lastMessage = React.useMemo(() => {
    if (!mostRecentMessageInfo) {
      return <div className={css.noMessage}>No messages</div>;
    }
    const previewText = username ? `${username}: ${message}` : message;
    return (
      <>
        <div className={css.longTextEllipsis}>{previewText}</div>
        <div className={css.lastActivity}>{lastActivity}</div>
      </>
    );
  }, [lastActivity, message, mostRecentMessageInfo, username]);

  return (
    <div className={css.subchannelContainer} onClick={onClickThread}>
      <SWMansionIcon icon="message-square" size={22} />
      <div className={css.subchannelInfo}>
        <div className={css.longTextEllipsis}>{threadInfo.name}</div>
        <div className={css.lastMessage}>{lastMessage}</div>
      </div>
    </div>
  );
}

export default Subchannel;
