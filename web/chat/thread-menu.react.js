// @flow

import classNames from 'classnames';
import * as React from 'react';

import { type ThreadInfo } from 'lib/types/thread-types';

import SWMansionIcon from '../SWMansionIcon.react';
import css from './thread-menu.css';

type ThreadMenuProps = {
  +threadInfo: ThreadInfo,
};

function ThreadMenu(props: ThreadMenuProps): React.Node {
  const [isOpen, setIsOpen] = React.useState(false);

  // eslint-disable-next-line no-unused-vars
  const { threadInfo } = props;

  const menuItems = [];

  const menuActionListClasses = classNames(css.topBarMenuActionList, {
    [css.disabled]: !isOpen,
  });

  const clickOutsideCallback = React.useCallback(() => {
    window.removeEventListener('click', clickOutsideCallback);
    if (isOpen) {
      setIsOpen(false);
    }
  }, [isOpen]);

  React.useEffect(() => {
    if (!window || !isOpen) {
      return undefined;
    }
    window.addEventListener('click', clickOutsideCallback);
    return () => window.removeEventListener('click', clickOutsideCallback);
  }, [clickOutsideCallback, isOpen]);

  if (menuItems.length === 0) {
    return null;
  }

  return (
    <div>
      <button
        className={css.topBarMenuButton}
        onClick={() => {
          setIsOpen(!isOpen);
        }}
      >
        <SWMansionIcon icon="menu-vertical" size={20} />
      </button>
      <div className={menuActionListClasses}>{menuItems}</div>
    </div>
  );
}

export default ThreadMenu;
