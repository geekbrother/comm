// @flow

import * as React from 'react';
import { View, StyleSheet } from 'react-native';

import { useSelector } from '../redux/redux-utils';
import type { ChatMessageInfoItemWithHeight } from '../types/chat-types';
import { DummyChatInputBar } from './chat-input-bar.react';
import { useMessageListScreenWidth } from './composed-message-width';
import { getSidebarThreadInfo } from './sidebar-navigation';

type Props = {
  +sourceMessage: ChatMessageInfoItemWithHeight,
  +onInputBarMeasured: (height: number) => mixed,
};

function SidebarInputBarHeightMeasurer(props: Props): React.Node {
  const { sourceMessage, onInputBarMeasured } = props;

  const width = useMessageListScreenWidth();

  const viewerID = useSelector(
    state => state.currentUserInfo && state.currentUserInfo.id,
  );
  const sidebarThreadInfo = React.useMemo(() => {
    return getSidebarThreadInfo(sourceMessage, viewerID);
  }, [sourceMessage, viewerID]);
  if (!sidebarThreadInfo) {
    return null;
  }

  return (
    <View style={[styles.dummy, { width }]}>
      <DummyChatInputBar
        threadInfo={sidebarThreadInfo}
        onHeightMeasured={onInputBarMeasured}
      />
    </View>
  );
}

const styles = StyleSheet.create({
  dummy: {
    opacity: 0,
    position: 'absolute',
  },
});

export default SidebarInputBarHeightMeasurer;
