// @flow

import * as React from 'react';

import { useModalContext } from '../../modals/modal-provider.react';
import css from '../../style.css';
import Modal from '../modal.react';
import LogInModal from './log-in-modal.react';

type BaseProps = {
  +inOrderTo: string,
};
type Props = {
  ...BaseProps,
  +setModal: (modal: ?React.Node) => void,
};
class LogInFirstModal extends React.PureComponent<Props> {
  render(): React.Node {
    return (
      <Modal name="Log in" onClose={this.clearModal}>
        <div className={css['modal-body']}>
          <p>
            {`In order to ${this.props.inOrderTo}, you'll first need to `}
            <a
              href="#"
              className={css['show-login-modal']}
              onClick={this.onClickLogIn}
            >
              log in
            </a>
            {'.'}
          </p>
        </div>
      </Modal>
    );
  }

  clearModal: () => void = () => {
    this.props.setModal(null);
  };

  onClickLogIn: (event: SyntheticEvent<HTMLAnchorElement>) => void = event => {
    event.preventDefault();
    this.props.setModal(<LogInModal />);
  };
}

function ConnectedLoginFirstModal(props: BaseProps): React.Node {
  const modalContext = useModalContext();

  return <LogInFirstModal {...props} setModal={modalContext.setModal} />;
}

export default ConnectedLoginFirstModal;
