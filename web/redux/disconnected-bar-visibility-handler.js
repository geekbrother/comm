// @flow

import { useDisconnectedBarVisibility } from 'lib/hooks/disconnected-bar';

function DisconnectedBarVisibilityHandler(): null {
  useDisconnectedBarVisibility(true);
  return null;
}

export default DisconnectedBarVisibilityHandler;
