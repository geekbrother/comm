// @flow

import classNames from 'classnames';
import * as React from 'react';

import css from './chat-thread-list.css';

type SearchClearProps = {
  +active: boolean,
  +onClick: () => void,
};

function SearchClear(props: SearchClearProps): React.Node {
  const { active, onClick } = props;
  const searchClassNames = classNames({
    [css.clearSearch]: true,
    [css.clearSearchDisabled]: !active,
  });
  return (
    <button className={searchClassNames} onClick={onClick}>
      &times;
    </button>
  );
}

export default SearchClear;
