// @flow

import invariant from 'invariant';
import * as React from 'react';
import ReactDOM from 'react-dom';

import css from './menu-portal.css';

type Props = {
  +children: React.Node,
};
type MenuPortalContextType = {
  +renderInMenuPortal: (itemToRender: React.Node) => void,
};

const MenuPortalContext: React.Context<?MenuPortalContextType> = React.createContext<?MenuPortalContextType>(
  {
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
  const value = React.useMemo(
    () => ({
      renderInMenuPortal,
    }),
    [renderInMenuPortal],
  );

  return (
    <>
      <MenuPortalContext.Provider value={value}>
        {children}
      </MenuPortalContext.Provider>
      <div ref={portalRef} className={css.portal}></div>
    </>
  );
}

function useRenderInMenuPortal(): (itemToRender: React.Node) => void {
  const context = React.useContext(MenuPortalContext);
  invariant(context, 'ModalPortalContext not found');

  return context.renderInMenuPortal;
}

export { MenuPortalProvider, useRenderInMenuPortal };
