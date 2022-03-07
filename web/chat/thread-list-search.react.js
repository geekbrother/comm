// @flow

import * as React from 'react';

import Search from '../components/search.react';

type Props = {
  +searchText: string,
  +onChangeText: (searchText: string) => mixed,
};

function ThreadListSearch(props: Props): React.Node {
  const { searchText, onChangeText } = props;

  return (
    <Search
      onChangeText={onChangeText}
      searchText={searchText}
      placeholder="Search threads"
    />
  );
}

export default ThreadListSearch;
