// @flow

import * as React from 'react';

import type { UserListItem } from 'lib/types/user-types';

import AddMembersItem from './add-members-item.react';
import css from './members-modal.css';

type AddMemberItemGroupProps = {
  +header: string,
  +userInfos: $ReadOnlyArray<UserListItem>,
  +onUserClick: (userID: string) => void,
  +usersAdded: $ReadOnly<Set<string>>,
};
function AddMembersItemGroup(props: AddMemberItemGroupProps): React.Node {
  const { userInfos, onUserClick, usersAdded, header } = props;
  const capitalizedHeader =
    header.charAt(0).toUpperCase() + header.substring(1);

  const sortedUserInfos = React.useMemo(() => {
    return [...userInfos].sort((a, b) => a.username.localeCompare(b.username));
  }, [userInfos]);

  const userInfosComponents = React.useMemo(
    () =>
      sortedUserInfos.map(userInfo => (
        <AddMembersItem
          key={userInfo.id}
          userInfo={userInfo}
          onClick={onUserClick}
          userAdded={usersAdded.has(userInfo.id)}
        />
      )),
    [onUserClick, sortedUserInfos, usersAdded],
  );

  return (
    <>
      <div className={css.addMemberItemsGroupHeader}>{capitalizedHeader}:</div>
      {userInfosComponents}
    </>
  );
}

export default AddMembersItemGroup;
