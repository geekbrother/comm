// @flow

import * as React from 'react';

import { logOut } from 'lib/actions/user-actions';
import { preRequestUserStateSelector } from 'lib/selectors/account-selectors';
import { useServerCall } from 'lib/utils/action-utils';

import { useModalContext } from '../modals/modal-provider.react';
import { useSelector } from '../redux/redux-utils';
import SWMansionIcon from '../SWMansionIcon.react';
import css from './account-settings.css';
import PasswordChangeModal from './password-change-modal';

function AccountSettings(): React.Node {
  const sendLogoutRequest = useServerCall(logOut);
  const preRequestUserState = useSelector(preRequestUserStateSelector);
  const logOutUser = React.useCallback(() => {
    sendLogoutRequest(preRequestUserState);
  }, [sendLogoutRequest, preRequestUserState]);

  const { pushModal } = useModalContext();
  const showPasswordChangeModal = React.useCallback(
    () => pushModal(<PasswordChangeModal />),
    [pushModal],
  );

  const currentUserInfo = useSelector(state => state.currentUserInfo);
  if (!currentUserInfo || currentUserInfo.anonymous) {
    return null;
  }
  const { username } = currentUserInfo;

  return (
    <div className={css.container}>
      <h4 className={css.header}>My Account</h4>
      <div className={css.content}>
        <ul>
          <li>
            <p className={css.logoutContainer}>
              <span className={css.logoutLabel}>{'Logged in as '}</span>
              <span className={css.username}>{username}</span>
            </p>
            <button className={css.button} onClick={logOutUser}>
              Log out
            </button>
          </li>
          <li>
            <span>Password</span>
            <span className={css.passwordContainer}>
              <span className={css.password}>******</span>
              <a
                className={css.editPasswordLink}
                onClick={showPasswordChangeModal}
              >
                <SWMansionIcon icon="edit" size={22} />
              </a>
            </span>
          </li>
          <li>
            <span>Friend List</span>
            <button className={css.button}>See List</button>
          </li>
          <li>
            <span>Block List</span>
            <button className={css.button}>See List</button>
          </li>
        </ul>
      </div>
    </div>
  );
}

export default AccountSettings;
