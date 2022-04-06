// @flow

import invariant from 'invariant';
import * as React from 'react';

type Props = {
  +children: React.Node,
};
type ModalContextType = {
  +modals: $ReadOnlyArray<React.Node>,
  +pushModal: (?React.Node) => void,
  +popModal: () => void,
  +clearModals: () => void,
};

const ModalContext: React.Context<?ModalContextType> = React.createContext<?ModalContextType>(
  {
    modals: [],
    pushModal: () => {},
    popModal: () => {},
    clearModals: () => {},
  },
);

function ModalProvider(props: Props): React.Node {
  const { children } = props;
  const [modals, setModals] = React.useState<$ReadOnlyArray<React.Node>>([]);
  const popModal = React.useCallback(
    () => setModals(oldModals => [...oldModals.slice(0, oldModals.length - 1)]),
    [],
  );
  const pushModal = React.useCallback(newModal => {
    if (newModal) {
      setModals(oldModals => [...oldModals, newModal]);
    }
  }, []);

  const clearModals = React.useCallback(() => setModals([]), []);

  const value = React.useMemo(
    () => ({
      modals,
      pushModal,
      popModal,
      clearModals,
    }),
    [modals, pushModal, popModal, clearModals],
  );

  return (
    <ModalContext.Provider value={value}>{children}</ModalContext.Provider>
  );
}

function useModalContext(): ModalContextType {
  const context = React.useContext(ModalContext);
  invariant(context, 'ModalContext not found');

  return context;
}

export { ModalProvider, useModalContext };
