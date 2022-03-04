// @flow

import * as React from 'react';

import NavigationPanel from './navigation-panel.react';

function SettingsSwitcher(): React.Node {
  const accountSettingsNavigationItem = React.useMemo(
    () => (
      <p>
        <a>My Account</a>
      </p>
    ),
    [],
  );

  const navigationItems = React.useMemo(
    () => [{ tab: 'settings', link: accountSettingsNavigationItem }],
    [accountSettingsNavigationItem],
  );

  return <NavigationPanel navigationItems={navigationItems} />;
}

export default SettingsSwitcher;
