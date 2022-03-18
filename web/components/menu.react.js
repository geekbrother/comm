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
  const [isOpen, setIsOpen] = React.useState(false);

  const buttonRef = React.useRef();
  const { renderMenu, setMenuPosition } = useRenderMenu();
  const { icon, children, variant = 'thread-actions', onChange } = props;

  const updatePosition = React.useCallback(() => {
    if (buttonRef.current && isOpen) {
      const { top, left } = buttonRef.current.getBoundingClientRect();
      setMenuPosition({ top, left });
    }
  }, [isOpen, setMenuPosition]);

  React.useEffect(updatePosition, [updatePosition]);

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

  React.useEffect(
    () =>
      renderMenu(previous => {
        if (isOpen) {
          return menuActionList;
        } else if (previous === menuActionList) {
          return null;
        } else {
          return previous;
        }
      }),
    [isOpen, menuActionList, renderMenu],
  );

  const closeMenuCallback = React.useCallback(() => {
    document.removeEventListener('click', closeMenuCallback);
    if (isOpen) {
      setIsOpen(false);
      renderMenu(previous => {
        if (previous === menuActionList) {
          return null;
        } else {
          return previous;
        }
      });
    }
  }, [isOpen, menuActionList, renderMenu]);

  React.useEffect(() => {
    onChange?.(isOpen);
  }, [isOpen, onChange]);

  React.useEffect(() => {
    if (!window) {
      return undefined;
    }

    window.addEventListener('resize', updatePosition);
    return () => window.removeEventListener('resize', updatePosition);
  }, [updatePosition]);

  React.useEffect(() => {
    if (!document || !isOpen) {
      return undefined;
    }
    document.addEventListener('click', closeMenuCallback);
    return closeMenuCallback;
  }, [closeMenuCallback, isOpen]);

  const switchMenuCallback = React.useCallback(() => {
    updatePosition();
    setIsOpen(isMenuOpen => !isMenuOpen);
  }, [updatePosition]);

  if (React.Children.count(children) === 0) {
    return null;
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
    </>
  );
}

export default Menu;
