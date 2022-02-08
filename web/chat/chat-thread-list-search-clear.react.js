// @flow

import { faTimes } from '@fortawesome/free-solid-svg-icons';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import classNames from 'classnames';
import * as React from 'react';

import css from './chat-thread-list.css';

type SearchClearProps = {
  +active: boolean,
  +onClick: () => void,
};

function SearchClear(props: SearchClearProps): React.Node {
  const { active, onClick } = props;
  const searchClassNames = classNames(css.clearSearch, {
    [css.clearSearchDisabled]: !active,
  });
  return (
    <button className={searchClassNames} onClick={onClick}>
      <FontAwesomeIcon icon={faTimes} />
    </button>
  );
}

export default SearchClear;
