// @flow

import * as React from 'react';

import type { UserListItem } from 'lib/types/user-types';

import AddMembersItem from './add-members-item.react';
import css from './members-modal.css';

type AddMemberItemGroupProps = {
  +header: string,
  +userInfos: $ReadOnlyArray<UserListItem>,
  +onUserClick: (userID: string) => void,
  +usersAdded: $ReadOnlyArray<string>,
};
function AddMembersItemGroup(props: AddMemberItemGroupProps): React.Node {
  const { userInfos, onUserClick, usersAdded, header } = props;

  const userInfosComponents = React.useMemo(
    () =>
      [...userInfos]
        .sort((a, b) => a.username.localeCompare(b.username))
        .map(userInfo => (
          <AddMembersItem
            key={userInfo.id}
            userInfo={userInfo}
            onClick={onUserClick}
            userAdded={usersAdded.includes(userInfo.id)}
          />
        )),
    [onUserClick, userInfos, usersAdded],
  );

  return (
    <div className={css.addMemberItemsGroup}>
      <div className={css.addMemberItemsGroupHeader}>{header}:</div>
      {userInfosComponents}
    </div>
  );
}

export default AddMembersItemGroup;
