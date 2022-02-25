// @flow

import * as React from 'react';

import { useSelector } from '../redux/redux-utils';
import css from './account-settings.css';

function AccountSettings(): React.Node {
  const currentUserInfo = useSelector(state => state.currentUserInfo);
  const username =
    currentUserInfo && !currentUserInfo.anonymous
      ? currentUserInfo.username
      : undefined;

  return (
    <div className={css.container}>
      <h4 className={css.header}>My Account</h4>
      <div className={css.content}>
        <ul>
          <li>
            <p>
              {'Logged in as '}
              <span className={css.username}>{username}</span>
            </p>
          </li>
        </ul>
      </div>
    </div>
  );
}

export default AccountSettings;
