// @flow
import {
  faUserMinus,
  faUserPlus,
  faUserShield,
  faUserSlash,
} from '@fortawesome/free-solid-svg-icons';
import * as React from 'react';

import { useRelationshipPrompt } from 'lib/hooks/relationship-prompt';
import { userRelationshipStatus } from 'lib/types/relationship-types';
import type { ThreadInfo } from 'lib/types/thread-types';

import RelationshipPromptButton from './relationship-prompt-button';
import RelationshipPromptButtonContainer from './relationship-prompt-button-container';

type Props = { +threadInfo: ThreadInfo };

const RelationshipPrompt: React.ComponentType<Props> = React.memo<Props>(
  function RelationshipPrompt(props: Props) {
    const { threadInfo } = props;
    const {
      otherUserInfo,
      callbacks: { blockUser, unblockUser, friendUser, unfriendUser },
    } = useRelationshipPrompt(threadInfo);
    if (!otherUserInfo?.username) {
      return null;
    }
    const relationshipStatus = otherUserInfo.relationshipStatus;

    if (relationshipStatus === userRelationshipStatus.FRIEND) {
      return null;
    } else if (relationshipStatus === userRelationshipStatus.BLOCKED_VIEWER) {
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
    } else if (
      relationshipStatus === userRelationshipStatus.BOTH_BLOCKED ||
      relationshipStatus === userRelationshipStatus.BLOCKED_BY_VIEWER
    ) {
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
    } else if (relationshipStatus === userRelationshipStatus.REQUEST_RECEIVED) {
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
    } else if (relationshipStatus === userRelationshipStatus.REQUEST_SENT) {
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
    } else {
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

export default RelationshipPrompt;
