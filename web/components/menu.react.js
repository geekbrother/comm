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
    currentMenu: currentlyRenderedMenu,
  } = useRenderMenu();
  const { icon, children, variant = 'thread-actions', onChange } = props;

  const menuActionListClasses = React.useMemo(
    () =>
      classnames(css.menuActionList, {
        [css.menuActionListThreadActions]: variant === 'thread-actions',
        [css.menuActionListMemberActions]: variant === 'member-actions',
      }),
    [variant],
  );

  const menuActionList = React.useMemo(() => {
    return <div className={menuActionListClasses}>{children}</div>;
  }, [children, menuActionListClasses]);

  const updatePosition = React.useCallback(() => {
    if (buttonRef.current && currentlyRenderedMenu === menuActionList) {
      const { top, left } = buttonRef.current.getBoundingClientRect();
      setMenuPosition({ top, left });
    }
  }, [currentlyRenderedMenu, menuActionList, setMenuPosition]);

  // useLayoutEffect is necessary so that the menu position is immediately
  // updated in the first render of component
  React.useLayoutEffect(() => {
    updatePosition();
  }, [updatePosition]);

  const closeMenuCallback = React.useCallback(() => {
    closeMenu(menuActionList);
    onChange?.(false);
  }, [closeMenu, menuActionList, onChange]);

  React.useEffect(() => {
    if (currentlyRenderedMenu === menuActionList) {
      document.addEventListener('click', closeMenuCallback);
    }
    return () => {
      document.removeEventListener('click', closeMenuCallback);
    };
  }, [closeMenuCallback, currentlyRenderedMenu, menuActionList]);

  const prevActionListRef = React.useRef<React.Node>(null);
  React.useEffect(() => {
    if (prevActionListRef.current === currentlyRenderedMenu) {
      renderMenu(menuActionList);
    }
    prevActionListRef.current = menuActionList;
  }, [currentlyRenderedMenu, menuActionList, renderMenu]);

  React.useEffect(() => {
    if (!window) {
      return undefined;
    }

    window.addEventListener('resize', updatePosition);
    return () => window.removeEventListener('resize', updatePosition);
  }, [updatePosition]);

  React.useEffect(() => {
    return () => closeMenu(prevActionListRef.current);
  }, [closeMenu]);

  const onClickMenuCallback = React.useCallback(() => {
    renderMenu(menuActionList);
    onChange?.(true);
  }, [menuActionList, onChange, renderMenu]);

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
