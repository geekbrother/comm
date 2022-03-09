// @flow

import classnames from 'classnames';
import * as React from 'react';

import css from './menu.css';

type MenuPosition = 'left' | 'right' | 'bottom';
type MenuSize = 'small' | 'medium';

type MenuProps = {
  icon: React.Node,
  children: $ReadOnlyArray<React.Node>,
  position?: MenuPosition,
  size?: MenuSize,
  light?: boolean,
};

function Menu(props: MenuProps): React.Node {
  const [isOpen, setIsOpen] = React.useState(false);

  const {
    icon,
    children,
    position = 'bottom',
    size = 'medium',
    light = false,
  } = props;

  const closeMenuCallback = React.useCallback(() => {
    document.removeEventListener('click', closeMenuCallback);
    if (isOpen) {
      setIsOpen(false);
    }
  }, [isOpen]);

  React.useEffect(() => {
    if (!document || !isOpen) {
      return undefined;
    }
    document.addEventListener('click', closeMenuCallback);
    return () => document.removeEventListener('click', closeMenuCallback);
  }, [closeMenuCallback, isOpen]);

  const switchMenuCallback = React.useCallback(() => {
    setIsOpen(isMenuOpen => !isMenuOpen);
  }, []);

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

    menuActionList = (
      <div className={css.menuActionListContainer}>
        <div className={menuActionListClasses}>{children}</div>
      </div>
    );
  }

  return (
    <div>
      <button className={css.menuButton} onClick={switchMenuCallback}>
        {icon}
      </button>
      {menuActionList}
    </div>
  );
}

export default Menu;
