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
  +readOnly: boolean,
  +enabled: boolean,
  +name: string,
  +icon: 'message-square' | 'calendar',
  +copy: string,
};

function AppListing(props: Props): React.Node {
  const { id, readOnly, enabled, name, icon, copy } = props;
  const dispatch = useDispatch();

  const enableApp = React.useCallback(
    () => dispatch({ type: enableAppActionType, payload: id }),
    [dispatch, id],
  );

  const disableApp = React.useCallback(() => {
    dispatch({ type: disableAppActionType, payload: id });
  }, [dispatch, id]);

  const actionButton = React.useMemo(() => {
    const switchIcon = enabled ? faCheckCircle : faPlusCircle;
    if (readOnly) {
      return (
        <div className={css.appListingIconState}>
          <FontAwesomeIcon color="#808080" icon={switchIcon} />
        </div>
      );
    }
    const color = enabled ? '#00c853' : '#ebebeb';
    return (
      <div
        className={css.appListingIconState}
        onClick={enabled ? disableApp : enableApp}
      >
        <FontAwesomeIcon
          color={color}
          icon={enabled ? faCheckCircle : faPlusCircle}
        />
      </div>
    );
  }, [readOnly, disableApp, enableApp, enabled]);
  return (
    <div className={css.appListingContainer}>
      <div className={css.appListingIcon}>
        <SWMansionIcon icon={icon} size={20} />
      </div>
      <div className={css.appListingTextContainer}>
        <div className={css.appName}>{name}</div>
        <div className={css.appCopy}>{copy}</div>
      </div>
      {actionButton}
    </div>
  );
}

export default AppListing;
