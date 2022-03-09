// @flow

import invariant from 'invariant';
import * as React from 'react';
import ReactDOM from 'react-dom';

import css from './menu-portal.css';

type Props = {
  +children: React.Node,
};
type MenuPortalContextType = {
  portalRef: { current: mixed } | null,
  renderInMenuPortal: (itemToRender: React.Node) => void,
};

const MenuPortalContext: React.Context<?MenuPortalContextType> = React.createContext<?MenuPortalContextType>(
  {
    portalRef: null,
    renderInMenuPortal: () => {},
  },
);

function MenuPortalProvider(props: Props): React.Node {
  const { children } = props;
  const portalRef = React.useRef();

  const renderInMenuPortal = React.useCallback(
    (itemToRender: React.Node) =>
      ReactDOM.createPortal(itemToRender, portalRef.current),
    [],
  );

  const value = React.useMemo(() => {
    return {
      portalRef,
      renderInMenuPortal,
    };
  }, [renderInMenuPortal]);

  return (
    <>
      <MenuPortalContext.Provider value={value}>
        {children}
      </MenuPortalContext.Provider>
      <div ref={portalRef} className={css.portal}></div>
    </>
  );
}

function useMenuPortalContext(): MenuPortalContextType {
  const context = React.useContext(MenuPortalContext);
  invariant(context, 'ModalContext not found');

  return context;
}

export { MenuPortalProvider, useMenuPortalContext };
