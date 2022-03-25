// @flow

import classnames from 'classnames';
import * as React from 'react';

import { useRenderMenu } from '../menu-provider.react';
import css from './menu.css';

type MenuVariant = 'thread-actions' | 'member-actions';

type MenuProps = {
  +icon: React.Node,
  +children?: React.Node,
  +variant?: MenuVariant,
  +onChange?: boolean => void,
};

function Menu(props: MenuProps): React.Node {
  const buttonRef = React.useRef();
  const {
    renderMenu,
    setMenuPosition,
    closeMenu,
    setCurrentOpenMenu,
    currentOpenMenu,
  } = useRenderMenu();
  const { icon, children, variant = 'thread-actions', onChange } = props;
  const ourSymbol = React.useRef(Symbol());
  const menuActionListClasses = React.useMemo(
    () =>
      classnames(css.menuActionList, {
        [css.menuActionListThreadActions]: variant === 'thread-actions',
        [css.menuActionListMemberActions]: variant === 'member-actions',
      }),
    [variant],
  );

  const menuActionList = React.useMemo(
    () => <div className={menuActionListClasses}>{children}</div>,
    [children, menuActionListClasses],
  );

  const updatePosition = React.useCallback(() => {
    if (buttonRef.current && currentOpenMenu === ourSymbol.current) {
      const { top, left } = buttonRef.current.getBoundingClientRect();
      setMenuPosition({ top, left });
    }
  }, [currentOpenMenu, setMenuPosition]);

  React.useEffect(() => {
    if (!window) {
      return undefined;
    }

    window.addEventListener('resize', updatePosition);
    return () => window.removeEventListener('resize', updatePosition);
  }, [updatePosition]);

  // useLayoutEffect is necessary so that the menu position is immediately
  // updated in the first render of component
  React.useLayoutEffect(() => {
    updatePosition();
  }, [updatePosition]);

  const closeMenuCallback = React.useCallback(() => {
    closeMenu(menuActionList);
  }, [closeMenu, menuActionList]);

  const isOurMenuOpen = currentOpenMenu === ourSymbol.current;

  React.useEffect(() => {
    onChange?.(isOurMenuOpen);
  }, [isOurMenuOpen, onChange]);

  React.useEffect(() => {
    if (ourSymbol.current !== currentOpenMenu) {
      return undefined;
    }
    document.addEventListener('click', closeMenuCallback);
    return () => {
      document.removeEventListener('click', closeMenuCallback);
    };
  }, [closeMenuCallback, currentOpenMenu, menuActionList]);

  const prevActionListRef = React.useRef<React.Node>(null);
  React.useEffect(() => {
    if (currentOpenMenu !== ourSymbol.current) {
      prevActionListRef.current = null;
      return;
    }
    if (prevActionListRef.current === menuActionList) {
      return;
    }
    renderMenu(menuActionList);

    prevActionListRef.current = menuActionList;
  }, [currentOpenMenu, menuActionList, renderMenu]);

  React.useEffect(() => {
    return () => closeMenu(prevActionListRef.current);
  }, [closeMenu]);

  const onClickMenuCallback = React.useCallback(() => {
    setCurrentOpenMenu(ourSymbol.current);
  }, [setCurrentOpenMenu]);

  if (React.Children.count(children) === 0) {
    return null;
  }

  return (
    <button
      ref={buttonRef}
      className={css.menuButton}
      onClick={onClickMenuCallback}
    >
      {icon}
    </button>
  );
}

export default Menu;
