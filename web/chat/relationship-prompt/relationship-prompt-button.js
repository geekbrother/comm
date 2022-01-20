// @flow

import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import * as React from 'react';

import css from './relationship-prompt.css';

type Props = {
  +text: string,
  +icon: any,
  +color?: string,
  +textColor?: string,
  +onClick: () => void,
};
function RelationshipPromptButton(props: Props): React.Node {
  const { text, icon, color, textColor, onClick } = props;
  const buttonStyle = React.useMemo(
    () => ({
      backgroundColor: color ?? 'darkblue',
      color: textColor ?? 'white',
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
