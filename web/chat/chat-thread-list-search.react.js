// @flow

import * as React from 'react';

import SearchClear from './chat-thread-list-search-clear.react';
import css from './chat-thread-list.css';

type SearchProps = {
  +searchText: string,
  +onChangeText: (searchText: string) => mixed,
};

function Search(props: SearchProps): React.Node {
  const { searchText, onChangeText } = props;

  const [showClearButton, setShowClearButton] = React.useState(
    searchText.length > 0,
  );

  const onClear = React.useCallback(() => {
    onChangeText('');
  }, [onChangeText]);

  const onChange = React.useCallback(
    event => {
      onChangeText(event.target.value);
    },
    [onChangeText],
  );

  React.useEffect(() => {
    if (searchText.length > 0) {
      setShowClearButton(true);
    } else {
      setShowClearButton(false);
    }
  }, [searchText]);

  return (
    <div className={css.searchContainer}>
      <input
        className={css.searchInput}
        onChange={onChange}
        value={searchText}
        type="text"
        placeholder="Search threads"
      />
      <SearchClear onClick={onClear} active={showClearButton} />
    </div>
  );
}

export default Search;
