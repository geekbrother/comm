// @flow

import classNames from 'classnames';
import _ from 'lodash';
import * as React from 'react';

import { stringForUser } from 'lib/shared/user-utils';
import {
  type ThreadInfo,
  type RelativeMemberInfo,
} from 'lib/types/thread-types';

import ThreadMember from './member.react';
import css from './members-modal.css';

type Props = {
  +threadInfo: ThreadInfo,
  +threadMembers: $ReadOnlyArray<RelativeMemberInfo>,
};

function ThreadMembersList(props: Props): React.Node {
  const { threadMembers, threadInfo } = props;
  const [openMenus, setOpenMenus] = React.useState([]);
  const userExists = threadMembers.length > 0;

  const groupedByFirstLetterMembers = React.useMemo(
    () => _.groupBy(threadMembers, member => stringForUser(member)[0]),
    [threadMembers],
  );

  const groupedMembersList = React.useMemo(
    () =>
      _.toPairs(groupedByFirstLetterMembers)
        .sort((a, b) => a[0].localeCompare(b[0]))
        .map(([letter, users]) => {
          const userList = users.map((user: RelativeMemberInfo) => (
            <ThreadMember
              key={user.id}
              memberInfo={user}
              threadInfo={threadInfo}
              onMenuChange={menuOpen => {
                if (menuOpen) {
                  setOpenMenus(menus => [...menus, user.id]);
                } else {
                  setOpenMenus(menus => menus.filter(id => id !== user.id));
                }
              }}
            />
          ));
          const letterHeader = (
            <div className={css.memberletterHeader} key={letter}>
              {letter.toUpperCase()}
            </div>
          );
          return (
            <React.Fragment key={letter}>
              {letterHeader}
              {userList}
            </React.Fragment>
          );
        }),
    [groupedByFirstLetterMembers, threadInfo],
  );
  let content = groupedMembersList;
  if (!userExists) {
    content = (
      <div className={css.noUsers}>
        No matching users were found in the thread!
      </div>
    );
  }
  const membersListClasses = classNames(css.membersList, {
    [css.noScroll]: !!openMenus.length,
  });
  return <div className={membersListClasses}>{content}</div>;
}

export default ThreadMembersList;
