// @flow

import * as React from 'react';

import { useFilteredChatListData } from 'lib/selectors/chat-selectors';
import { threadSearchIndex } from 'lib/selectors/nav-selectors';
import { childThreadInfos } from 'lib/selectors/thread-selectors';
import { threadIsChannel } from 'lib/shared/thread-utils';

import Search from '../../../components/search.react';
import { useSelector } from '../../../redux/redux-utils';
import Modal from '../../modal.react';
import Subchannel from './subchannel.react';
import css from './subchannels-modal.css';

type Props = {
  +threadID: string,
  +onClose: () => void,
};

function SubchannelsModal(props: Props): React.Node {
  const { threadID, onClose } = props;
  const [searchText, setSearchText] = React.useState('');

  const childThreads = useSelector(state => childThreadInfos(state)[threadID]);
  const subchannelsIDs = React.useMemo(() => {
    if (!childThreads) {
      return [];
    }
    return childThreads
      .filter(threadIsChannel)
      .map(threadInfo => threadInfo.id);
  }, [childThreads]);

  const filterSubchannels = React.useCallback(
    thread => subchannelsIDs.includes(thread?.id),
    [subchannelsIDs],
  );
  const allSubchannelsChatList = useFilteredChatListData(filterSubchannels);

  const searchIndex = useSelector(threadSearchIndex);

  const filteredSubchannelsChatList = React.useMemo(() => {
    if (!searchText.length) {
      return allSubchannelsChatList;
    }
    const searchResultsIDs = searchIndex.getSearchResults(searchText);
    return allSubchannelsChatList.filter(item =>
      searchResultsIDs.includes(item.threadInfo.id),
    );
  }, [allSubchannelsChatList, searchIndex, searchText]);

  const subchannels = React.useMemo(() => {
    if (!filteredSubchannelsChatList.length) {
      return (
        <div className={css.noSubchannels}>
          No matching subchannels were found in the thread!
        </div>
      );
    }
    return filteredSubchannelsChatList.map(childThreadItem => (
      <Subchannel
        chatThreadItem={childThreadItem}
        key={childThreadItem.threadInfo.id}
      />
    ));
  }, [filteredSubchannelsChatList]);

  return (
    <Modal name="Subchannels" onClose={onClose}>
      <div className={css.subchannelsModalContent}>
        <Search
          searchText={searchText}
          onChangeText={setSearchText}
          placeholder="Search"
        />
        <div className={css.subchannelsListContainer}>{subchannels}</div>
      </div>
    </Modal>
  );
}

export default SubchannelsModal;
