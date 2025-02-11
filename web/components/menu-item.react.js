// @flow

import classNames from 'classnames';
import * as React from 'react';

import SWMansionIcon, { type Icon } from '../SWMansionIcon.react';
import css from './menu.css';

type MenuItemProps = {
  +onClick?: () => mixed,
  +icon: Icon,
  +text: string,
  +dangerous?: boolean,
};

function MenuItem(props: MenuItemProps): React.Node {
  const { onClick, icon, text, dangerous } = props;

  const itemClasses = classNames(css.menuAction, {
    [css.menuActionDangerous]: dangerous,
  });
  return (
    <button className={itemClasses} onClick={onClick}>
      <div className={css.menuActionIcon}>
        <SWMansionIcon size="100%" icon={icon} />
      </div>
      <div>{text}</div>
    </button>
  );
}

const MemoizedMenuItem: React.ComponentType<MenuItemProps> = React.memo(
  MenuItem,
);

export default MemoizedMenuItem;
