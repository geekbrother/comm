// @flow

import * as React from 'react';

import { userStoreSearchIndex as userStoreSearchIndexSelector } from 'lib/selectors/user-selectors';
import type { AccountUserInfo } from 'lib/types/user-types';

import { useSelector } from '../../redux/redux-utils';
import css from './user-list.css';

export type UserRowProps = {
  +userInfo: AccountUserInfo,
};

type Props = {
  +userRowComponent: React.ComponentType<UserRowProps>,
  +filterUser: (userInfo: AccountUserInfo) => boolean,
  +usersCompareFunction: (
    user1: AccountUserInfo,
    user2: AccountUserInfo,
  ) => number,
  +searchText: string,
};

export function UserList(props: Props): React.Node {
  const {
    userRowComponent,
    filterUser,
    usersCompareFunction,
    searchText,
  } = props;
  const userInfos = useSelector(state => state.userStore.userInfos);
  const userStoreSearchIndex = useSelector(userStoreSearchIndexSelector);

  const searchResult = React.useMemo(
    () => userStoreSearchIndex.getSearchResults(searchText),
    [searchText, userStoreSearchIndex],
  );

  const users = React.useMemo(() => {
    const filteredUsers = [];
    const userIDs = searchText ? searchResult : Object.keys(userInfos);
    for (const id of userIDs) {
      const { username, relationshipStatus } = userInfos[id];
      if (!username) {
        continue;
      }
      const userInfo = {
        id,
        username,
        relationshipStatus,
      };
      if (filterUser(userInfo)) {
        filteredUsers.push(userInfo);
      }
    }
    filteredUsers.sort(usersCompareFunction);
    return filteredUsers;
  }, [filterUser, searchResult, searchText, userInfos, usersCompareFunction]);

  const userRows = React.useMemo(() => {
    const UserRow = userRowComponent;
    return users.map(user => <UserRow userInfo={user} key={user.id} />);
  }, [users, userRowComponent]);

  return <div className={css.container}>{userRows}</div>;
}
