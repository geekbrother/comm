// @flow

import type { BaseNavInfo } from 'lib/types/nav-types';
import type { ThreadInfo } from 'lib/types/thread-types';

export type NavInfo = {
  ...$Exact<BaseNavInfo>,
  +tab: 'calendar' | 'chat' | 'settings',
  +activeChatThreadID: ?string,
  +pendingThread?: ThreadInfo,
  +settingsSection?: 'account',
};

export const updateNavInfoActionType = 'UPDATE_NAV_INFO';
