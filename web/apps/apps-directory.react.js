// @flow

import * as React from 'react';
import { useSelector } from 'react-redux';

import AppListing from './app-listing.react';
import css from './apps.css';

const APP_DIRECTORY_DATA = [
  {
    id: 'chat',
    alwaysEnabled: true,
    appName: 'Chat',
    appIcon: 'message-square',
    appCopy: 'Keep in touch with your community',
  },
  {
    id: 'calendar',
    alwaysEnabled: false,
    appName: 'Calendar',
    appIcon: 'calendar',
    appCopy: 'Shared calendar for your community',
  },
];

function AppsDirectory(): React.Node {
  const enabledApps = useSelector(state => state.enabledApps);

  const appData = React.useMemo(
    () =>
      APP_DIRECTORY_DATA.map(app => ({
        ...app,
        enabled: enabledApps[app.id] ?? true,
      })),
    [enabledApps],
  );

  const appItems = React.useMemo(
    () => appData.map(item => <AppListing key={item.id} {...item} />),
    [appData],
  );

  return (
    <div className={css.appsDirectoryContainer}>
      <div className={css.appsHeader}>Choose Apps</div>
      <div className={css.appsDirectoryList}>{appItems}</div>
    </div>
  );
}

export default AppsDirectory;
