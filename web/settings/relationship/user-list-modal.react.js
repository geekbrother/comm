// @flow

import * as React from 'react';

import type { AccountUserInfo } from 'lib/types/user-types';

import SearchModal from '../../modals/search-modal.react';
import { UserList, type UserRowProps } from './user-list.react';

type Props = {
  +onClose: () => void,
  +name: string,
  +userRowComponent: React.ComponentType<UserRowProps>,
  +filterUser: (userInfo: AccountUserInfo) => boolean,
  +usersCompareFunction: (
    user1: AccountUserInfo,
    user2: AccountUserInfo,
  ) => number,
};

function UserListModal(props: Props): React.Node {
  const {
    onClose,
    name,
    userRowComponent,
    filterUser,
    usersCompareFunction,
  } = props;
  return (
    <SearchModal
      name={name}
      size="large"
      searchPlaceholder="Search by name"
      onClose={onClose}
    >
      {(searchText: string) => (
        <UserList
          userRowComponent={userRowComponent}
          filterUser={filterUser}
          usersCompareFunction={usersCompareFunction}
          searchText={searchText}
        />
      )}
    </SearchModal>
  );
}

export default UserListModal;
