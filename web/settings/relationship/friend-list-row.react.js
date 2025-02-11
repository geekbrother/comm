// @flow

import classnames from 'classnames';
import * as React from 'react';

import { useRelationshipCallbacks } from 'lib/hooks/relationship-prompt';
import { userRelationshipStatus } from 'lib/types/relationship-types';

import SWMansionIcon from '../../SWMansionIcon.react';
import css from './friend-list-row.css';
import type { UserRowProps } from './user-list.react';

function FriendListRow(props: UserRowProps): React.Node {
  const { userInfo } = props;

  const { friendUser, unfriendUser } = useRelationshipCallbacks(userInfo.id);
  let buttons = null;
  if (userInfo.relationshipStatus === userRelationshipStatus.REQUEST_SENT) {
    buttons = (
      <button
        className={classnames([css.button, css.destructive])}
        onClick={unfriendUser}
      >
        Cancel request
      </button>
    );
  } else if (
    userInfo.relationshipStatus === userRelationshipStatus.REQUEST_RECEIVED
  ) {
    buttons = (
      <>
        <button className={css.button} onClick={friendUser}>
          Accept
        </button>
        <button
          className={classnames([css.button, css.destructive])}
          onClick={unfriendUser}
        >
          Reject
        </button>
      </>
    );
  } else if (userInfo.relationshipStatus === userRelationshipStatus.FRIEND) {
    buttons = (
      <button className={classnames([css.button, css.edit_button])}>
        <SWMansionIcon icon="edit" size={22} />
      </button>
    );
  }

  return (
    <div className={css.container}>
      <div className={css.usernameContainer}>{userInfo.username}</div>
      <div className={css.buttons}>{buttons}</div>
    </div>
  );
}

export default FriendListRow;
