// @flow

import * as React from 'react';

import AppSwitcher from './app-switcher.react';
import css from './sidebar.css';
import Spaces from './spaces.react';

function SideBar(): React.Node {
  return (
    <aside className={css.container}>
      <Spaces />
      <AppSwitcher />
    </aside>
  );
}

export default SideBar;
