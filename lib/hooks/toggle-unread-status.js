// @flow

import * as React from 'react';

import {
  setThreadUnreadStatus,
  setThreadUnreadStatusActionTypes,
} from '../actions/activity-actions';
import type {
  SetThreadUnreadStatusPayload,
  SetThreadUnreadStatusRequest,
} from '../types/activity-types';
import type { ThreadInfo } from '../types/thread-types';
import { useDispatchActionPromise, useServerCall } from '../utils/action-utils';

function useToggleUnreadStatus(
  threadInfo: ThreadInfo,
  mostRecentNonLocalMessage: ?string,
  onAfter: () => void,
): () => void {
  const dispatchActionPromise = useDispatchActionPromise();
  const boundSetThreadUnreadStatus: (
    request: SetThreadUnreadStatusRequest,
  ) => Promise<SetThreadUnreadStatusPayload> = useServerCall(
    setThreadUnreadStatus,
  );
  const toggleUnreadStatus = React.useCallback(() => {
    const { unread } = threadInfo.currentUser;
    const request = {
      threadID: threadInfo.id,
      unread: !unread,
      latestMessage: mostRecentNonLocalMessage,
    };
    dispatchActionPromise(
      setThreadUnreadStatusActionTypes,
      boundSetThreadUnreadStatus(request),
      undefined,
      {
        threadID: threadInfo.id,
        unread: !unread,
      },
    );
    onAfter();
  }, [
    threadInfo,
    mostRecentNonLocalMessage,
    dispatchActionPromise,
    onAfter,
    boundSetThreadUnreadStatus,
  ]);

  return toggleUnreadStatus;
}

export default useToggleUnreadStatus;
