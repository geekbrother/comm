// @flow

import * as React from 'react';

import useModal from './use-modal.react';

type Props = {
  +children: React.Node,
};

type ModalContentType = {
  modal?: React.Node,
  handleModal: ?Function,
};

const ModalContext: React.Context<?ModalContentType> = React.createContext<?ModalContentType>();

function ModalProvider(props: Props): React.Node {
  const { children } = props;
  const { modal, handleModal } = useModal();

  return (
    <ModalContext.Provider value={{ modal, handleModal }}>
      {children}
    </ModalContext.Provider>
  );
}

export { ModalContext, ModalProvider };
