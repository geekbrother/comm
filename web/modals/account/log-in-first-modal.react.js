// @flow

import * as React from 'react';

import { useModalContext } from '../../modals/modal-provider.react';
import css from '../../style.css';
import Modal from '../modal.react';
import LogInModal from './log-in-modal.react';

type Props = {
  +inOrderTo: string,
};
function LogInFirstModal(props: Props): React.Node {
  const modalContext = useModalContext();

  const onClickLogIn: (
    event: SyntheticEvent<HTMLAnchorElement>,
  ) => void = event => {
    event.preventDefault();
    modalContext.setModal(<LogInModal />);
  };

  return (
    <Modal name="Log in" clearModal={this.clearModal}>
      <div className={css['modal-body']}>
        <p>
          {`In order to ${props.inOrderTo}, you'll first need to `}
          <a
            href="#"
            className={css['show-login-modal']}
            onClick={onClickLogIn}
          >
            log in
          </a>
          {'.'}
        </p>
      </div>
    </Modal>
  );
}

export default LogInFirstModal;
