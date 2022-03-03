// @flow

import classNames from 'classnames';
import * as React from 'react';

import { useSelector } from '../redux/redux-utils';
import type { NavigationTab } from '../types/nav-types';
import css from './left-layout-aside.css';

type Props = {
  +navigationItems: $ReadOnlyArray<{
    +tab: NavigationTab,
    +link: React.Node,
  }>,
};

function NavigationPanel(props: Props): React.Node {
  const { navigationItems } = props;
  const navInfo = useSelector(state => state.navInfo);

  const items = React.useMemo(
    () =>
      navigationItems.map(item => (
        <li
          key={item.tab}
          className={classNames({
            [css['current-tab']]: navInfo.tab === item.tab,
          })}
        >
          {item.link}
        </li>
      )),
    [navInfo.tab, navigationItems],
  );

  return (
    <div className={css.navigationPanelContainer}>
      <ul>{items}</ul>
    </div>
  );
}

export default NavigationPanel;
