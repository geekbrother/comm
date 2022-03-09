// @flow

import classnames from 'classnames';
import * as React from 'react';

import { useMenuPortalContext } from '../menu-portal-provider.react';
import css from './menu.css';

type MenuPosition = 'left' | 'right' | 'bottom';
type MenuSize = 'small' | 'medium';

type MenuProps = {
  icon: React.Node,
  children: $ReadOnlyArray<React.Node>,
  position?: MenuPosition,
  size?: MenuSize,
  light?: boolean,
  onChange?: boolean => void,
};

function Menu(props: MenuProps): React.Node {
  const [isOpen, setIsOpen] = React.useState(false);
  const [buttonPosition, setButtonPosition] = React.useState(null);

  const buttonRef = React.useRef();
  const { renderInMenuPortal } = useMenuPortalContext();
  const {
    icon,
    children,
    position = 'bottom',
    size = 'medium',
    light = false,
    onChange,
  } = props;

  const updatePosition = React.useCallback(() => {
    if (buttonRef.current) {
      setButtonPosition(buttonRef.current.getBoundingClientRect());
    }
  }, []);

  React.useEffect(updatePosition, [updatePosition]);

  const closeMenuCallback = React.useCallback(() => {
    document.removeEventListener('click', closeMenuCallback);
    if (isOpen) {
      setIsOpen(false);
    }
  }, [isOpen]);

  React.useEffect(() => {
    if (onChange) {
      onChange(isOpen);
    }
  }, [isOpen, onChange]);

  React.useEffect(() => {
    if (!window) {
      return undefined;
    }

    window.addEventListener('resize', updatePosition);
    return () => window.removeEventListener('resize', updatePosition);
  });
  React.useEffect(() => {
    if (!document || !isOpen) {
      return undefined;
    }
    document.addEventListener('click', closeMenuCallback);
    return () => document.removeEventListener('click', closeMenuCallback);
  }, [closeMenuCallback, isOpen]);

  const switchMenuCallback = React.useCallback(() => {
    updatePosition();
    setIsOpen(isMenuOpen => !isMenuOpen);
  }, [updatePosition]);

  if (children.length === 0) {
    return null;
  }

  let menuActionList = null;
  if (isOpen) {
    const menuActionListClasses = classnames(css.menuActionList, {
      [css.menuActionListBottom]: position === 'bottom',
      [css.menuActionListLeft]: position === 'left',
      [css.menuActionListMedium]: size === 'medium',
      [css.menuActionListSmall]: size === 'small',
      [css.menuActionListLight]: light,
    });

    const actionListStyle = buttonPosition
      ? {
          top: buttonPosition.top,
          left: buttonPosition.left,
        }
      : {};
    menuActionList = renderInMenuPortal(
      <div style={actionListStyle} className={css.menuActionListContainer}>
        <div className={menuActionListClasses}>{children}</div>
      </div>,
    );
  }

  return (
    <>
      <button
        ref={buttonRef}
        className={css.menuButton}
        onClick={switchMenuCallback}
      >
        {icon}
      </button>
      {menuActionList}
    </>
  );
}

export default Menu;
