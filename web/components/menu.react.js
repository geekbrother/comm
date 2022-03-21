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
    currentMenu,
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
    if (buttonRef.current && currentMenu === menuActionList) {
      const { top, left } = buttonRef.current.getBoundingClientRect();
      setMenuPosition({ top, left });
    }
  }, [currentMenu, menuActionList, setMenuPosition]);

  React.useLayoutEffect(() => {
    updatePosition();
  }, [updatePosition]);

  const closeMenuCallback = React.useCallback(() => {
    document.removeEventListener('click', closeMenuCallback);
    closeMenu(menuActionList);
    onChange?.(false);
  }, [closeMenu, menuActionList, onChange]);

  React.useEffect(() => {
    if (!window) {
      return undefined;
    }

    window.addEventListener('resize', updatePosition);
    return () => window.removeEventListener('resize', updatePosition);
  }, [updatePosition]);

  React.useEffect(() => {
    return closeMenuCallback;
  }, [closeMenuCallback]);

  const onClickMenuCallback = React.useCallback(() => {
    renderMenu(menuActionList);
    document.addEventListener('click', closeMenuCallback);
    onChange?.(true);
  }, [closeMenuCallback, menuActionList, onChange, renderMenu]);

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
