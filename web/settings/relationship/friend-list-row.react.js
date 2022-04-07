// @flow

import classnames from 'classnames';
import * as React from 'react';

import { userRelationshipStatus } from 'lib/types/relationship-types';

import SWMansionIcon from '../../SWMansionIcon.react';
import css from './friend-list-row.css';
import type { UserRowProps } from './user-list.react';

function FriendListRow(props: UserRowProps): React.Node {
  const { userInfo } = props;
  let buttons = null;
  if (userInfo.relationshipStatus === userRelationshipStatus.REQUEST_SENT) {
    buttons = (
      <div className={classnames([css.button, css.destructive])}>
        Cancel request
      </div>
    );
  } else if (
    userInfo.relationshipStatus === userRelationshipStatus.REQUEST_RECEIVED
  ) {
    buttons = (
      <>
        <div className={css.button}>Accept</div>
        <div className={classnames([css.button, css.destructive])}>Reject</div>
      </>
    );
  } else if (userInfo.relationshipStatus === userRelationshipStatus.FRIEND) {
    buttons = <SWMansionIcon icon="edit" size={22} />;
  }

  return (
    <div className={css.container}>
      {userInfo.username}
      <div className={css.buttons}>{buttons}</div>
    </div>
  );
}

export default FriendListRow;
