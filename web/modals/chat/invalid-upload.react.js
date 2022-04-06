// @flow

import * as React from 'react';

import { useModalContext } from '../../modals/modal-provider.react';
import css from '../../style.css';
import Modal from '../modal.react';

type Props = {
  +clearModals: () => void,
};
class InvalidUploadModal extends React.PureComponent<Props> {
  render(): React.Node {
    return (
      <Modal name="Invalid upload" onClose={this.props.clearModals}>
        <div className={css['modal-body']}>
          <p>We don&apos;t support that file type yet :(</p>
        </div>
      </Modal>
    );
  }
}

function ConnectedInvalidUploadModal(): React.Node {
  const modalContext = useModalContext();

  return <InvalidUploadModal clearModals={modalContext.clearModals} />;
}

export default ConnectedInvalidUploadModal;
