// @flow

import * as React from 'react';

import { threadInfoSelector } from 'lib/selectors/thread-selectors';
import { memberHasAdminPowers, memberIsAdmin } from 'lib/shared/thread-utils';
import { stringForUser } from 'lib/shared/user-utils';
import { type RelativeMemberInfo } from 'lib/types/thread-types';

import Tabs from '../../../components/tabs.react';
import { useSelector } from '../../../redux/redux-utils';
import SearchModal from '../../search-modal.react';
import ThreadMembersList from './members-list.react';

type ContentProps = {
  +searchText: string,
  +threadID: string,
};
function ThreadMembersModalContent(props: ContentProps): React.Node {
  const { threadID, searchText } = props;

  const [tab, setTab] = React.useState<'All Members' | 'Admins'>('All Members');

  const threadInfo = useSelector(state => threadInfoSelector(state)[threadID]);
  const { members: threadMembersNotFiltered } = threadInfo;

  const allMembers = React.useMemo(
    () =>
      threadMembersNotFiltered.filter((member: RelativeMemberInfo) =>
        stringForUser(member)
          .toLowerCase()
          .startsWith(searchText.toLowerCase()),
      ),
    [searchText, threadMembersNotFiltered],
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
      <Tabs.Item id="All Members" header="All Members">
        <ThreadMembersList threadInfo={threadInfo} threadMembers={allMembers} />
      </Tabs.Item>
    ),
    [allMembers, threadInfo],
  );

  const allAdminsTab = React.useMemo(
    () => (
      <Tabs.Item id="Admins" header="Admins">
        <ThreadMembersList
          threadInfo={threadInfo}
          threadMembers={adminMembers}
        />
      </Tabs.Item>
    ),
    [adminMembers, threadInfo],
  );

  return (
    <Tabs.Container activeTab={tab} setTab={setTab}>
      {allUsersTab}
      {allAdminsTab}
    </Tabs.Container>
  );
}

type Props = {
  +threadID: string,
  +onClose: () => void,
};
function ThreadMembersModal(props: Props): React.Node {
  const { onClose, threadID } = props;
  const renderModalContent = React.useCallback(
    (searchText: string) => (
      <ThreadMembersModalContent threadID={threadID} searchText={searchText} />
    ),
    [threadID],
  );
  return (
    <SearchModal
      name="Members"
      searchPlaceholder="Search members"
      onClose={onClose}
    >
      {renderModalContent}
    </SearchModal>
  );
}

export default ThreadMembersModal;
