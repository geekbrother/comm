// @flow

import * as React from 'react';

import { threadInfoSelector } from 'lib/selectors/thread-selectors';
import { memberHasAdminPowers, memberIsAdmin } from 'lib/shared/thread-utils';
import { stringForUser } from 'lib/shared/user-utils';
import { type RelativeMemberInfo } from 'lib/types/thread-types';

import Search from '../../../components/search.react';
import Tabs from '../../../components/tabs.react';
import { useSelector } from '../../../redux/redux-utils';
import Modal from '../../modal.react';
import ThreadMembersList from './members-list.react';
import css from './members-modal.css';

type Props = {
  +threadID: string,
  +onClose: () => void,
};
function ThreadMembersModal(props: Props): React.Node {
  const { threadID, onClose } = props;

  const [tab, setTab] = React.useState('All Members');
  const [search, setSearch] = React.useState('');

  const threadInfo = useSelector(state => threadInfoSelector(state)[threadID]);
  const { members: threadMembersNotFiltered } = threadInfo;

  const allMembers = React.useMemo(
    () =>
      threadMembersNotFiltered.filter((member: RelativeMemberInfo) =>
        stringForUser(member).toLowerCase().startsWith(search.toLowerCase()),
      ),
    [search, threadMembersNotFiltered],
  );
  const adminMembers = React.useMemo(
    () =>
      allMembers.filter(
        (member: RelativeMemberInfo) =>
          memberIsAdmin(member, threadInfo) || memberHasAdminPowers(member),
      ),
    [allMembers, threadInfo],
  );

  const allUsersTab = React.useMemo(
    () => (
      <ThreadMembersList
        threadInfo={threadInfo}
        threadMembers={allMembers}
      ></ThreadMembersList>
    ),
    [allMembers, threadInfo],
  );
  const adminsTab = React.useMemo(
    () => (
      <ThreadMembersList
        threadInfo={threadInfo}
        threadMembers={adminMembers}
      ></ThreadMembersList>
    ),
    [adminMembers, threadInfo],
  );
  const tabs = React.useMemo(
    () => [
      { id: 'All Members', header: 'All Members', content: allUsersTab },
      { id: 'Admins', header: 'Admins', content: adminsTab },
    ],
    [adminsTab, allUsersTab],
  );

  return (
    <Modal name="Members" onClose={onClose}>
      <div className={css.membersContainer}>
        <Search
          onChangeText={text => setSearch(text)}
          searchText={search}
          placeholder="Search members"
        />
        <Tabs activeTab={tab} setTab={setTab} tabs={tabs} />
      </div>
    </Modal>
  );
}

export default ThreadMembersModal;
