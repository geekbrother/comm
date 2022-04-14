// @flow

import * as React from 'react';

import Button from '../../components/button.react.js';
import { useModalContext } from '../../modals/modal-provider.react';
import Modal from '../modal.react';
import css from './invalid-upload.css';

type Props = {
  +clearModals: () => void,
};
class InvalidUploadModal extends React.PureComponent<Props> {
  render(): React.Node {
    return (
      <Modal name="Invalid upload" onClose={this.props.clearModals}>
        <div className={css.modal_body}>
          <p>We don&apos;t support that file type yet :(</p>
          <Button
            onClick={this.props.clearModals}
            type="submit"
            variant="primary"
            className={css.ok_button}
          >
            OK
          </Button>
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
