// @flow

import classnames from 'classnames';
import * as React from 'react';

import { useRenderMenu } from '../menu-provider.react';
import css from './menu.css';

type MenuVariant = 'thread-actions' | 'member-actions';

type MenuProps = {
  +icon: React.Node,
  +children: $ReadOnlyArray<React.Node>,
  +variant?: MenuVariant,
  +onChange?: boolean => void,
};

function Menu(props: MenuProps): React.Node {
  const [isOpen, setIsOpen] = React.useState(false);
  const [buttonPosition, setButtonPosition] = React.useState(null);

  const buttonRef = React.useRef();
  const renderMenu = useRenderMenu();
  const { icon, children, variant = 'thread-actions', onChange } = props;

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
      [css.menuActionListThreadActions]: variant === 'thread-actions',
      [css.menuActionListMemberActions]: variant === 'member-actions',
    });

    const actionListStyle = buttonPosition
      ? {
          top: buttonPosition.top,
          left: buttonPosition.left,
        }
      : {};
    menuActionList = renderMenu(
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
