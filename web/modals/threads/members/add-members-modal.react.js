// @flow

import * as React from 'react';

import Button from '../../../components/button.react';
import SearchModal from '../../search-modal.react';
import AddMembersList from './add-members-list.react';
import css from './members-modal.css';

type ContentProps = {
  +searchText: string,
  +threadID: string,
  +onClose: () => void,
};

function AddMembersModalContent(props: ContentProps): React.Node {
  const { onClose } = props;

  const [pendingUsersToAdd, setpendingUsersToAdd] = React.useState<
    $ReadOnlyArray<string>,
  >([]);

  const userSearchResults = [];

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
