// @flow

import { type IconDefinition } from '@fortawesome/fontawesome-common-types';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import * as React from 'react';

import css from './relationship-prompt.css';

type Props = {
  +text: string,
  +icon: IconDefinition,
  +color?: string,
  +textColor?: string,
  +onClick: () => void,
};
function RelationshipPromptButton(props: Props): React.Node {
  const { text, icon, color, textColor, onClick } = props;
  const buttonStyle = React.useMemo(
    () => ({
      backgroundColor: color ?? 'var(--relationship-button-green)',
      color: textColor ?? 'var(--relationship-button-text)',
    }),
    [color, textColor],
  );

  return (
    <button className={css.promptButton} onClick={onClick} style={buttonStyle}>
      <FontAwesomeIcon icon={icon} className={css.promptIcon} />
      <div>{text}</div>
    </button>
  );
}

export default RelationshipPromptButton;
