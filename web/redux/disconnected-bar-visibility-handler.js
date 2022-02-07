// @flow

import * as React from 'react';

import { useDisconnectedBarVisibilityHandler } from 'lib/hooks/disconnected-bar';

function useNetworkConnected() {
  const [networkConnected, setNetworkConnected] = React.useState(true);
  React.useEffect(() => {
    if (window) {
      window.addEventListener('online', () => setNetworkConnected(true));
      window.addEventListener('offline', () => setNetworkConnected(false));
    }
  }, []);

  return networkConnected;
}

function DisconnectedBarVisibilityHandler(): null {
  const networkConnected = useNetworkConnected();
  useDisconnectedBarVisibilityHandler(networkConnected);
  return null;
}

export default DisconnectedBarVisibilityHandler;
