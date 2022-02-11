// @flow

import * as React from 'react';

function useModal(): {
  modal: ?React.Node,
  handleModal: () => void,
} {
  const [modal, setModal] = React.useState(false);
  const handleModal = React.useCallback(() => {
    setModal(modal);
  }, [modal]);

  return { modal, handleModal };
}

export default useModal;
