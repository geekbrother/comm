// @flow

import _groupBy from 'lodash/fp/groupBy';
import _toPairs from 'lodash/fp/toPairs';
import * as React from 'react';

import type { UserListItem } from 'lib/types/user-types';

import AddMembersItemGroup from './add-members-group.react';

type Props = {
  +userListItems: $ReadOnlyArray<UserListItem>,
  +pendingUsersToAdd: $ReadOnlyArray<string>,
  +switchUser: string => void,
};

function AddMembersList(props: Props): React.Node {
  const { userListItems, pendingUsersToAdd, switchUser } = props;

  const usersAvailableToAdd = userListItems.filter(user => !user.alertTitle);
  const usersUnavailableToAdd = userListItems.filter(user => user.alertTitle);

  const groupedAvailableUsersList = React.useMemo(
    () => _groupBy(userInfo => userInfo.notice)(usersAvailableToAdd),
    [usersAvailableToAdd],
  );

  const membersInParentThread = React.useMemo(
    () =>
      groupedAvailableUsersList['undefined']
        ? ['Users in parent channel', groupedAvailableUsersList['undefined']]
        : undefined,
    [groupedAvailableUsersList],
  );

  const sortedGroupedUsersList = React.useMemo(
    () => [
      ...(membersInParentThread ? [membersInParentThread] : []),
      ..._toPairs(groupedAvailableUsersList)
        .filter(group => group[0] !== 'undefined')
        .sort((a, b) => a[0].localeCompare(b[0])),
      ...(usersUnavailableToAdd.length
        ? [['Unavailable users', usersUnavailableToAdd]]
        : []),
    ],
    [groupedAvailableUsersList, membersInParentThread, usersUnavailableToAdd],
  );

  return sortedGroupedUsersList.map(([header, userInfos]) => (
    <AddMembersItemGroup
      key={header}
      header={header}
      userInfos={userInfos}
      onUserClick={switchUser}
      usersAdded={pendingUsersToAdd}
    />
  ));
}

export default AddMembersList;
