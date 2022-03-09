// @flow

import classnames from 'classnames';
import * as React from 'react';

import css from './tabs.css';

export type TabInfo = {
  id: string,
  header: string | React.Node,
  content: React.Node,
};

type Props = {
  +tabs: $ReadOnlyArray<TabInfo>,
  +activeTab: string,
  +setTab: string => mixed,
};

function Tabs(props: Props): React.Node {
  const { tabs, activeTab, setTab } = props;

  const headers = React.useMemo(
    () =>
      tabs.map(tab => {
        const isActive = tab.id === activeTab;
        const headerClasses = classnames(css.tabHeader, {
          [css.activeTabHeader]: isActive,
          [css.backgroundTabHeader]: !isActive,
        });
        return (
          <div
            className={headerClasses}
            key={tab.id}
            onClick={() => setTab(tab.id)}
          >
            {tab.header}
          </div>
        );
      }),
    [activeTab, setTab, tabs],
  );

  const content = React.useMemo(() => {
    const currentTab = tabs.find(tab => tab.id === activeTab);
    if (currentTab) {
      return currentTab.content;
    }
    return null;
  }, [activeTab, tabs]);

  return (
    <div className={css.tabsContainer}>
      <div className={css.tabsHeaderContainer}>{headers}</div>
      {content}
    </div>
  );
}

export default Tabs;
