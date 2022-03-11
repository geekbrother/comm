// @flow

import classnames from 'classnames';
import * as React from 'react';

import css from './tabs.css';

type TabsContainerProps = {
  +children?: React.ChildrenArray<?React.Element<typeof TabsItem>>,
  +activeTab: string,
  +setTab: string => mixed,
};

function TabsContainer(props: TabsContainerProps): React.Node {
  const { children, activeTab, setTab } = props;

  const headers = React.Children.map(children, tab => {
    const { id, header } = tab.props;
    const isActive = id === activeTab;
    const headerClasses = classnames(css.tabHeader, {
      [css.backgroundTabHeader]: !isActive,
    });
    return (
      <div className={headerClasses} key={id} onClick={() => setTab(id)}>
        {header}
      </div>
    );
  });

  const currentTab = React.Children.toArray(children).find(
    tab => tab.props.id === activeTab,
  );

  const currentContent = currentTab ? currentTab.props.children : null;

  return (
    <div className={css.tabsContainer}>
      <div className={css.tabsHeaderContainer}>{headers}</div>
      {currentContent}
    </div>
  );
}

type TabsItemProps = {
  +children: React.Node,
  +id: string,
  +header: React.Node,
};

function TabsItem(props: TabsItemProps): React.Node {
  const { children } = props;
  return children;
}

const Tabs = {
  Container: TabsContainer,
  Item: TabsItem,
};

export default Tabs;
