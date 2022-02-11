// @flow

import * as React from 'react';

import useModal from './use-modal.react';

type Props = {
  +children: React.Node,
};

let ModalContext: React.Context<*>;
const { Provider } = (ModalContext = React.createContext());

function ModalProvider(props: Props): React.Node {
  const { children } = props;
  const { modal, handleModal, modalContent } = useModal();

  return (
    <Provider value={{ modal, handleModal, modalContent }}>{children}</Provider>
  );
}

export { ModalContext, ModalProvider };
