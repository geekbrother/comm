// @flow

import * as React from 'react';

import {
  changeThreadSettingsActionTypes,
  changeThreadSettings,
} from '../actions/thread-actions';
import { createLoadingStatusSelector } from '../selectors/loading-selectors';
import type { LoadingStatus } from '../types/loading-types';
import { threadTypes, type ThreadInfo } from '../types/thread-types';
import { useServerCall, useDispatchActionPromise } from '../utils/action-utils';
import { useSelector } from '../utils/redux-utils';

type PromoteThreadType = {
  onClick: () => void,
  loading: LoadingStatus,
  error: any,
};

function usePromoteThread(threadInfo: ThreadInfo): PromoteThreadType {
  const dispatchActionPromise = useDispatchActionPromise();
  const [error, setError] = React.useState(null);
  const callChangeThreadSettings = useServerCall(changeThreadSettings);
  const loadingStatusSelector = createLoadingStatusSelector(
    changeThreadSettingsActionTypes,
  );

  const loadingStatus = useSelector(loadingStatusSelector);

  const onClick = React.useCallback(() => {
    try {
      dispatchActionPromise(
        changeThreadSettingsActionTypes,
        (async () => {
          return await callChangeThreadSettings({
            threadID: threadInfo.id,
            changes: { type: threadTypes.COMMUNITY_OPEN_SUBTHREAD },
          });
        })(),
      );
    } catch (e) {
      setError(e);
      console.error(e);
    }
  }, [threadInfo.id, callChangeThreadSettings, dispatchActionPromise]);

  return { onClick, loading: loadingStatus, error };
}

export { usePromoteThread };
