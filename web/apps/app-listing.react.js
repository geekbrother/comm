// @flow

import { faCheckCircle } from '@fortawesome/free-regular-svg-icons';
import { faPlusCircle } from '@fortawesome/free-solid-svg-icons';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import * as React from 'react';
import { useDispatch } from 'react-redux';

import {
  disableAppActionType,
  enableAppActionType,
} from 'lib/reducers/enabled-apps-reducer';
import type { SupportedApps } from 'lib/types/enabled-apps';

import SWMansionIcon from '../SWMansionIcon.react';
import css from './apps.css';

type Props = {
  +id: SupportedApps | 'chat',
  +alwaysEnabled: boolean,
  +enabled: boolean,
  +appName: string,
  +appIcon: 'message-square' | 'calendar',
  +appCopy: string,
};

function AppListing(props: Props): React.Node {
  const { id, alwaysEnabled, enabled, appName, appIcon, appCopy } = props;
  const dispatch = useDispatch();

  const enableApp = React.useCallback(
    () => dispatch({ type: enableAppActionType, payload: id }),
    [dispatch, id],
  );

  const disableApp = React.useCallback(() => {
    console.log('DISABLE');
    dispatch({ type: disableAppActionType, payload: id });
  }, [dispatch, id]);

  const actionButton = React.useMemo(() => {
    if (alwaysEnabled) {
      return (
        <div className={css.appListingIconState}>
          <FontAwesomeIcon color="#808080" icon={faCheckCircle} />
        </div>
      );
    }
    return (
      <div
        className={css.appListingIconState}
        onClick={enabled ? disableApp : enableApp}
      >
        <FontAwesomeIcon
          color={enabled ? 'green' : 'white'}
          icon={enabled ? faCheckCircle : faPlusCircle}
        />
      </div>
    );
  }, [alwaysEnabled, disableApp, enableApp, enabled]);
  return (
    <div className={css.appListingContainer}>
      <div className={css.appListingIcon}>
        <SWMansionIcon icon={appIcon} size={20} />
      </div>
      <div className={css.appListingTextContainer}>
        <div className={css.appName}> {appName}</div>
        <div className={css.appCopy}> {appCopy}</div>
      </div>
      {actionButton}
    </div>
  );
}

export default AppListing;
