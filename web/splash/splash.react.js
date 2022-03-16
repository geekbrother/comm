// @flow

import * as React from 'react';

import LogInModal from '../modals/account/log-in-modal.react';
import { useModalContext } from '../modals/modal-provider.react';
import css from './splash.css';

function ConnectedSplash(): React.Node {
  const modalContext = useModalContext();
  const onClickLogIn = React.useCallback(
    (event: SyntheticEvent<HTMLAnchorElement>) => {
      event.preventDefault();
      modalContext.setModal(<LogInModal />);
    },
    [modalContext],
  );

  return (
    <React.Fragment>
      <div onClick={onClickLogIn} className={css.loginContainer}>
        <h1>Log in</h1>
      </div>
      {modalContext.modal}
    </React.Fragment>
  );
}

export default ConnectedSplash;
