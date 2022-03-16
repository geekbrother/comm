// @flow

import invariant from 'invariant';
import * as React from 'react';

import css from './menu.css';

type Props = {
  +children: React.Node,
};
type MenuContextType = {
  +renderMenu: (
    React.Node | ((currentState: React.Node) => React.Node),
  ) => void,
};

const MenuContext: React.Context<?MenuContextType> = React.createContext<?MenuContextType>(
  {
    renderMenu: () => {},
  },
);

function MenuProvider(props: Props): React.Node {
  const { children } = props;
  const [menu, setMenu] = React.useState(null);

  const value = React.useMemo(
    () => ({
      renderMenu: setMenu,
    }),
    [setMenu],
  );
  return (
    <>
      <MenuContext.Provider value={value}>{children}</MenuContext.Provider>
      <div className={css.container}>{menu}</div>
    </>
  );
}

function useRenderMenu(): (
  React.Node | ((currentState: React.Node) => React.Node),
) => void {
  const context = React.useContext(MenuContext);
  invariant(context, 'MenuContext not found');

  return context.renderMenu;
}

export { MenuProvider, useRenderMenu };
