// @flow

import invariant from 'invariant';
import * as React from 'react';

import type { SetState } from 'lib/types/hook-types';

import css from './menu.css';

type MenuPosition = {
  +top: number,
  +left: number,
};
type Props = {
  +children: React.Node,
};
type MenuContextType = {
  +renderMenu: SetState<React.Node>,
  +setMenuPosition: SetState<MenuPosition>,
  +currentMenu: React.Node,
  +closeMenu: React.Node => void,
};

const MenuContext: React.Context<MenuContextType> = React.createContext<MenuContextType>(
  {
    renderMenu: () => {},
    setMenuPosition: () => {},
    currentMenu: null,
    closeMenu: () => {},
  },
);

function MenuProvider(props: Props): React.Node {
  const { children } = props;
  const [menu, setMenu] = React.useState(null);
  const [position, setPosition] = React.useState<MenuPosition>({
    top: 0,
    left: 0,
  });

  const closeMenu = React.useCallback(
    (menuToClose: React.Node) =>
      setMenu(oldMenu => {
        if (oldMenu === menuToClose) {
          return null;
        } else {
          return oldMenu;
        }
      }),
    [],
  );

  const value = React.useMemo(
    () => ({
      renderMenu: setMenu,
      setMenuPosition: setPosition,
      currentMenu: menu,
      closeMenu,
    }),
    [closeMenu, menu],
  );
  return (
    <>
      <MenuContext.Provider value={value}>{children}</MenuContext.Provider>
      <div style={position} className={css.container}>
        {menu}
      </div>
    </>
  );
}

function useRenderMenu(): MenuContextType {
  const context = React.useContext(MenuContext);
  invariant(context, 'MenuContext not found');

  return context;
}

export { MenuProvider, useRenderMenu };
