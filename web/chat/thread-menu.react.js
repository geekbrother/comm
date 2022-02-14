// @flow

import {
  faArrowRight,
  faBell,
  faCog,
  faCommentAlt,
  faPlusCircle,
  faUserFriends,
} from '@fortawesome/free-solid-svg-icons';
import classNames from 'classnames';
import * as React from 'react';

import { childThreadInfos } from 'lib/selectors/thread-selectors';
import { threadHasPermission } from 'lib/shared/thread-utils';
import {
  type ThreadInfo,
  threadTypes,
  threadPermissions,
} from 'lib/types/thread-types';

import { useSelector } from '../redux/redux-utils';
import SWMansionIcon from '../SWMansionIcon.react';
import ThreadMenuItem from './thread-menu-item.react';
import css from './thread-menu.css';

type ThreadMenuProps = {
  +threadInfo: ThreadInfo,
};

function ThreadMenu(props: ThreadMenuProps): React.Node {
  const [isOpen, setIsOpen] = React.useState(false);

  const { threadInfo } = props;

  const settingsItem = React.useMemo(
    () => <ThreadMenuItem key="settings" text="Settings" icon={faCog} />,
    [],
  );

  const notificatiosItem = React.useMemo(
    () => (
      <ThreadMenuItem key="notifications" text="Notifications" icon={faBell} />
    ),
    [],
  );

  const childThreads = useSelector(
    state => childThreadInfos(state)[threadInfo.id],
  );

  const membersItem = React.useMemo(() => {
    if (threadInfo.type === threadTypes.PERSONAL) {
      return null;
    }
    return <ThreadMenuItem key="members" text="Members" icon={faUserFriends} />;
  }, [threadInfo.type]);

  const sidebarItem = React.useMemo(() => {
    const sidebars =
      childThreads?.filter(
        childThreadInfo => childThreadInfo.type === threadTypes.SIDEBAR,
      ) ?? [];
    if (sidebars.length === 0) {
      return null;
    }
    return (
      <ThreadMenuItem key="sidebars" text="Sidebars" icon={faArrowRight} />
    );
  }, [childThreads]);

  const canCreateSubchannels = React.useMemo(
    () => threadHasPermission(threadInfo, threadPermissions.CREATE_SUBCHANNELS),
    [threadInfo],
  );

  const viewSubchannelsItem = React.useMemo(() => {
    const subchannels =
      childThreads?.filter(
        childThreadInfo => childThreadInfo.type !== threadTypes.SIDEBAR,
      ) ?? [];

    if (subchannels.length === 0 && !canCreateSubchannels) {
      return null;
    }
    return (
      <ThreadMenuItem
        key="subchannels"
        text="Subchannels"
        icon={faCommentAlt}
      />
    );
  }, [canCreateSubchannels, childThreads]);

  const createSubchannelsItem = React.useMemo(() => {
    if (!canCreateSubchannels) {
      return null;
    }
    return (
      <ThreadMenuItem
        key="newSubchannel"
        text="Create new subchannel"
        icon={faPlusCircle}
      />
    );
  }, [canCreateSubchannels]);

  const menuItems = React.useMemo(() => {
    const items = [
      settingsItem,
      notificatiosItem,
      membersItem,
      sidebarItem,
      viewSubchannelsItem,
      createSubchannelsItem,
    ];
    return items.filter(Boolean);
  }, [
    notificatiosItem,
    settingsItem,
    membersItem,
    sidebarItem,
    viewSubchannelsItem,
    createSubchannelsItem,
  ]);

  const menuActionListClasses = classNames(css.topBarMenuActionList, {
    [css.disabled]: !isOpen,
  });

  const clickOutsideCallback = React.useCallback(() => {
    window.removeEventListener('click', clickOutsideCallback);
    if (isOpen) {
      setIsOpen(false);
    }
  }, [isOpen]);

  React.useEffect(() => {
    if (!window || !isOpen) {
      return undefined;
    }
    window.addEventListener('click', clickOutsideCallback);
    return () => window.removeEventListener('click', clickOutsideCallback);
  }, [clickOutsideCallback, isOpen]);

  if (menuItems.length === 0) {
    return null;
  }

  return (
    <div>
      <button
        className={css.topBarMenuButton}
        onClick={() => {
          setIsOpen(!isOpen);
        }}
      >
        <SWMansionIcon icon="menu-vertical" size={20} />
      </button>
      <div className={menuActionListClasses}>{menuItems}</div>
    </div>
  );
}

export default ThreadMenu;
