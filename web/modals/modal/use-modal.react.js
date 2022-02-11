// @flow

import * as React from 'react';

function useModal(): {
  modal: ?React.Node,
  handleModal: () => void,
  modalContent: ?React.Node,
} {
  const [modal, setModal] = React.useState(false);
  const [modalContent, setModalContent] = React.useState(
    "I'm the Modal Content",
  );

  const handleModal = (content = false) => {
    setModal(!modal);
    if (content) {
      setModalContent(content);
    }
  };

  return { modal, handleModal, modalContent };
}

export default useModal;
