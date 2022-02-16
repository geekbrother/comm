// @flow

import * as React from 'react';

import { useModalContext } from '../../modals/modal-provider.react';
import css from '../../style.css';
import Modal from '../modal.react';

function InvalidUploadModal(): React.Node {
  const modalContext = useModalContext();

  return (
    <Modal name="Invalid upload" clearModal={modalContext.clearModal}>
      <div className={css['modal-body']}>
        <p>We don&apos;t support that file type yet :(</p>
      </div>
    </Modal>
  );
}

export default InvalidUploadModal;
