// @flow

import * as React from 'react';

import { useDisconnectedBarVisibilityHandler } from 'lib/hooks/disconnected-bar';

function useNetworkConnected() {
  const [networkConnected, setNetworkConnected] = React.useState(true);
  React.useEffect(() => {
    function handleOnline() {
      setNetworkConnected(true);
    }

    function handleOffline() {
      setNetworkConnected(false);
    }

    if (window) {
      window.addEventListener('online', handleOnline);
      window.addEventListener('offline', handleOffline);
    }
    return () => {
      if (window) {
        window.removeEventListener('online', handleOnline);
        window.removeEventListener('offline', handleOffline);
      }
    };
  }, []);

  return networkConnected;
}

function DisconnectedBarVisibilityHandler(): null {
  const networkConnected = useNetworkConnected();
  useDisconnectedBarVisibilityHandler(networkConnected);
  return null;
}

export default DisconnectedBarVisibilityHandler;
