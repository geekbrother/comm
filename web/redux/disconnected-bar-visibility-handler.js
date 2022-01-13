// @flow

import { useDisconnectedBarVisibilityHandler } from 'lib/hooks/disconnected-bar';

function DisconnectedBarVisibilityHandler(): null {
  useDisconnectedBarVisibilityHandler(true);
  return null;
}

export default DisconnectedBarVisibilityHandler;
