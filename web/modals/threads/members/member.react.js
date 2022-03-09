// @flow

import classNames from 'classnames';
import * as React from 'react';
import { useState } from 'react';

import { memberIsAdmin, memberHasAdminPowers } from 'lib/shared/thread-utils';
import { stringForUser } from 'lib/shared/user-utils';
import {
  type RelativeMemberInfo,
  type ThreadInfo,
} from 'lib/types/thread-types';

import Label from '../../../components/label.react';
import Menu from '../../../components/menu.react';
import SWMansionIcon from '../../../SWMansionIcon.react';
import css from './members-modal.css';
type Props = {
  +memberInfo: RelativeMemberInfo,
  +threadInfo: ThreadInfo,
  +onMenuChange: boolean => void,
};

function ThreadMember(props: Props): React.Node {
  const { memberInfo, threadInfo, onMenuChange } = props;
  const userName = stringForUser(memberInfo);
  const [isMenuOpen, setIsMenuOpen] = useState(false);

  React.useEffect(() => {
    onMenuChange(isMenuOpen);
  }, [isMenuOpen, onMenuChange]);

  const menuItems = [];

  const userSettingsIcon = React.useMemo(
    () => <SWMansionIcon icon="edit" size={17} />,
    [],
  );

  const label = React.useMemo(() => {
    if (memberIsAdmin(memberInfo, threadInfo)) {
      return <Label>Admin</Label>;
    } else if (memberHasAdminPowers(memberInfo)) {
      return <Label>Parent admin</Label>;
    }
    return null;
  }, [memberInfo, threadInfo]);

  const memberContainerClasses = classNames(css.memberContainer, {
    [css.memberContainerWithMenuOpen]: isMenuOpen,
  });

  return (
    <div className={memberContainerClasses}>
      <div className={css.memberInfo}>
        {userName} {label}
      </div>
      <div className={css.memberAction}>
        <Menu
          icon={userSettingsIcon}
          position="left"
          light
          size="small"
          onChange={setIsMenuOpen}
        >
          {menuItems}
        </Menu>
      </div>
    </div>
  );
}

export default ThreadMember;
