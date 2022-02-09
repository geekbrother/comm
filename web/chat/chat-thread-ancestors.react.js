// @flow
import classNames from 'classnames';
import * as React from 'react';

import { useAncestorThreads } from 'lib/shared/ancestor-threads';
import { memberHasAdminPowers, colorIsDark } from 'lib/shared/thread-utils';
import type { ThreadInfo, RelativeMemberInfo } from 'lib/types/thread-types';

import { useSelector } from '../redux/redux-utils';
import SWMansionIcon from '../SWMansionIcon.react';
import css from './chat-thread-ancestors.css';

type ThreadAncestorsProps = {
  +threadInfo: ThreadInfo,
};
function ThreadAncestors(props: ThreadAncestorsProps): React.Node {
  const { threadInfo } = props;
  const threadColor = threadInfo.color;
  const darkColor = colorIsDark(threadColor);
  const threadBackgroundColorStyle = React.useMemo(
    () => ({
      backgroundColor: `#${threadInfo.color}`,
      color: darkColor
        ? 'var(--thread-ancestor-color-light)'
        : 'var(--thread-ancestor-color-dark)',
    }),
    [darkColor, threadInfo.color],
  );
  const threadColorStyle = React.useMemo(
    () => ({ color: `#${threadInfo.color}` }),
    [threadInfo.color],
  );

  const ancestorThreads = useAncestorThreads(threadInfo);

  const userInfos = useSelector(state => state.userStore.userInfos);
  const community = ancestorThreads[0] ?? threadInfo;
  const keyserverOperatorUsername: ?string = React.useMemo(() => {
    for (const member: RelativeMemberInfo of community.members) {
      if (memberHasAdminPowers(member)) {
        return userInfos[member.id].username;
      }
    }
  }, [community, userInfos]);

  const keyserverInfo = React.useMemo(
    () => (
      <div className={css.ancestorKeyserver}>
        <div className={css.ancestorKeyserverOperator}>
          <SWMansionIcon icon="cloud" size={10} />
          <span>{keyserverOperatorUsername}</span>
        </div>
        <div
          style={threadBackgroundColorStyle}
          className={classNames(css.ancestorName, css.ancestorKeyserverName)}
        >
          {community.uiName}
        </div>
      </div>
    ),
    [community.uiName, keyserverOperatorUsername, threadBackgroundColorStyle],
  );

  const middlePath = React.useMemo(() => {
    if (ancestorThreads.length < 2) {
      return null;
    }
    return (
      <>
        <div className={css.ancestorSeparator}>
          <SWMansionIcon icon="chevron-right" size={10} />
        </div>
        <div style={threadBackgroundColorStyle} className={css.ancestorName}>
          ...
        </div>
      </>
    );
  }, [ancestorThreads.length, threadBackgroundColorStyle]);

  const currentThread = React.useMemo(() => {
    if (community === threadInfo) {
      return null;
    }
    return (
      <>
        <div className={css.ancestorSeparator}>
          <SWMansionIcon icon="chevron-right" size={10} />
        </div>
        <div style={threadBackgroundColorStyle} className={css.ancestorName}>
          {threadInfo.uiName}
        </div>
      </>
    );
  }, [community, threadBackgroundColorStyle, threadInfo]);

  return (
    <>
      <div className={css.ancestorThreadsContainer}>
        {keyserverInfo}
        {middlePath}
        {currentThread}
      </div>
      <button style={threadColorStyle} className={css.seeFullStructure}>
        See full structure
      </button>
    </>
  );
}

export default ThreadAncestors;
