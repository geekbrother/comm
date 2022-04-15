// @flow

import * as React from 'react';

import { threadInfoSelector } from 'lib/selectors/thread-selectors';
import {
  userSearchIndexForPotentialMembers,
  userInfoSelectorForPotentialMembers,
} from 'lib/selectors/user-selectors';
import { getPotentialMemberItems } from 'lib/shared/search-utils';
import { threadActualMembers } from 'lib/shared/thread-utils';

import Button from '../../../components/button.react';
import { useSelector } from '../../../redux/redux-utils';
import SearchModal from '../../search-modal.react';
import AddMembersList from './add-members-list.react';
import css from './members-modal.css';

type ContentProps = {
  +searchText: string,
  +threadID: string,
  +onClose: () => void,
};

function AddMembersModalContent(props: ContentProps): React.Node {
  const { searchText, threadID, onClose } = props;

  const [pendingUsersToAdd, setpendingUsersToAdd] = React.useState<
    $ReadOnlyArray<string>,
  >([]);

  const threadInfo = useSelector(state => threadInfoSelector(state)[threadID]);
  const { parentThreadID, community } = threadInfo;
  const parentThreadInfo = useSelector(state =>
    parentThreadID ? threadInfoSelector(state)[parentThreadID] : null,
  );
  const communityThreadInfo = useSelector(state =>
    community ? threadInfoSelector(state)[community] : null,
  );
  const otherUserInfos = useSelector(userInfoSelectorForPotentialMembers);
  const userSearchIndex = useSelector(userSearchIndexForPotentialMembers);
  const excludeUserIDs = React.useMemo(
    () => threadActualMembers(threadInfo.members),
    [threadInfo.members],
  );

  const userSearchResults = React.useMemo(() => {
    return getPotentialMemberItems(
      searchText,
      otherUserInfos,
      userSearchIndex,
      excludeUserIDs,
      parentThreadInfo,
      communityThreadInfo,
      threadInfo.type,
    );
  }, [
    communityThreadInfo,
    excludeUserIDs,
    otherUserInfos,
    parentThreadInfo,
    searchText,
    threadInfo.type,
    userSearchIndex,
  ]);

  const onSwitchUser = React.useCallback(
    userID =>
      setpendingUsersToAdd(users => {
        if (users.includes(userID)) {
          return users.filter(user => user !== userID);
        } else {
          return [...users, userID];
        }
      }),
    [],
  );

  return (
    <div className={css.addMembersContent}>
      <div className={css.addMembersListContainer}>
        <AddMembersList
          userListItems={userSearchResults}
          switchUser={onSwitchUser}
          pendingUsersToAdd={pendingUsersToAdd}
        />
      </div>
      <div className={css.addMembersFooter}>
        <Button onClick={onClose} variant="danger">
          Cancel
        </Button>
        <Button
          disabled={!pendingUsersToAdd.length}
          variant={pendingUsersToAdd.length ? 'primary' : 'secondary'}
          onClick={() => {}}
        >
          Add selected members
        </Button>
      </div>
    </div>
  );
}

type Props = {
  +threadID: string,
  +onClose: () => void,
};

function AddMembersModal(props: Props): React.Node {
  const { threadID, onClose } = props;

  const addMembersModalContent = React.useCallback(
    (searchText: string) => (
      <AddMembersModalContent
        searchText={searchText}
        threadID={threadID}
        onClose={onClose}
      />
    ),
    [onClose, threadID],
  );

  return (
    <SearchModal
      name="Add members"
      searchPlaceholder="Search members"
      onClose={onClose}
      size="fit-content"
    >
      {addMembersModalContent}
    </SearchModal>
  );
}

export default AddMembersModal;
