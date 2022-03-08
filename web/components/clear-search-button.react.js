// @flow

import { faTimesCircle } from '@fortawesome/free-solid-svg-icons';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import classNames from 'classnames';
import * as React from 'react';

import css from './search.css';

type ClearSearchButtonProps = {
  +active: boolean,
  +onClick: () => void,
};

function ClearSearchButton(props: ClearSearchButtonProps): React.Node {
  const { active, onClick } = props;
  const searchClassNames = classNames(css.clearSearch, {
    [css.clearSearchDisabled]: !active,
  });
  return (
    <button className={searchClassNames} onClick={onClick}>
      <FontAwesomeIcon icon={faTimesCircle} />
    </button>
  );
}

export default ClearSearchButton;
