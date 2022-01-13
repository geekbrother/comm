// @flow
import {
  faUserMinus,
  faUserPlus,
  faUserShield,
  faUserSlash,
} from '@fortawesome/free-solid-svg-icons';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import * as React from 'react';

import { useRelationshipPrompt } from 'lib/hooks/relationship-prompt.js';
import { userRelationshipStatus } from 'lib/types/relationship-types';
import type { ThreadInfo } from 'lib/types/thread-types';

import css from './relationship-prompt.css';

type Props = { threadInfo: ThreadInfo };

const RelationshipPrompt: React.ComponentType<Props> = React.memo<Props>(
  function RelationshipPrompt({ threadInfo }) {
    const {
      otherUserInfo,
      callbacks: { blockUser, unblockUser, friendUser, unfriendUser },
    } = useRelationshipPrompt(threadInfo);
    if (!otherUserInfo?.username) {
      return null;
    }

    switch (otherUserInfo.relationshipStatus) {
      case userRelationshipStatus.FRIEND:
        return null;
      case userRelationshipStatus.BLOCKED_VIEWER:
        return (
          <RelationshipPromptButtonContainer>
            <RelationshipPromptButton
              text="Block User"
              icon={faUserShield}
              color="red"
              onClick={blockUser}
            />
          </RelationshipPromptButtonContainer>
        );
      case userRelationshipStatus.BOTH_BLOCKED:
      case userRelationshipStatus.BLOCKED_BY_VIEWER:
        return (
          <RelationshipPromptButtonContainer>
            <RelationshipPromptButton
              text="Unblock User"
              icon={faUserShield}
              color="green"
              onClick={unblockUser}
            />
          </RelationshipPromptButtonContainer>
        );
      case userRelationshipStatus.REQUEST_RECEIVED:
        return (
          <RelationshipPromptButtonContainer>
            <RelationshipPromptButton
              text="Accept Friend Request"
              icon={faUserPlus}
              color="green"
              onClick={friendUser}
            />
            <RelationshipPromptButton
              text="Reject Friend Request"
              icon={faUserSlash}
              color="red"
              onClick={unfriendUser}
            />
          </RelationshipPromptButtonContainer>
        );

      case userRelationshipStatus.REQUEST_SENT:
        return (
          <RelationshipPromptButtonContainer>
            <RelationshipPromptButton
              text="Withdraw Friend Request"
              icon={faUserMinus}
              color="red"
              onClick={unfriendUser}
            />
          </RelationshipPromptButtonContainer>
        );
      default:
        return (
          <RelationshipPromptButtonContainer>
            <RelationshipPromptButton
              text="Add Friend"
              icon={faUserPlus}
              color="green"
              onClick={friendUser}
            />
            <RelationshipPromptButton
              text="Block User"
              icon={faUserShield}
              color="red"
              onClick={blockUser}
            />
          </RelationshipPromptButtonContainer>
        );
    }
  },
);

type ButtonProps = {
  text: string,
  icon: any,
  color?: string,
  textColor?: string,
  onClick: () => void,
};
function RelationshipPromptButton(props: ButtonProps) {
  return (
    <button
      className={css.promptButton}
      onClick={props.onClick}
      style={{
        backgroundColor: props.color ?? 'darkblue',
        color: props.textColor ?? 'white',
      }}
    >
      <FontAwesomeIcon icon={props.icon} className={css.promptIcon} />
      <div>{props.text}</div>
    </button>
  );
}
function RelationshipPromptButtonContainer(props: { children: any }) {
  return <div className={css.promptButtonContainer}>{props.children}</div>;
}

export default RelationshipPrompt;
