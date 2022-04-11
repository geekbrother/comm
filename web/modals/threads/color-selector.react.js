// @flow

import * as React from 'react';

import { selectedThreadColors } from 'lib/shared/thread-utils';

import ColorSelectorButton from './color-selector-button.react';
import css from './color-selector.css';

type ColorSelectorProps = {
  +currentThreadColor: string,
  +onColorSelection: (hex: string) => void,
};
function ColorSelector(props: ColorSelectorProps): React.Node {
  const { currentThreadColor, onColorSelection } = props;

  const colorSelectorButtons = React.useMemo(
    () =>
      selectedThreadColors.map(color => (
        <ColorSelectorButton
          key={color}
          color={color}
          currentThreadColor={currentThreadColor}
          onColorSelection={onColorSelection}
        />
      )),
    [currentThreadColor, onColorSelection],
  );

  return <div className={css.container}>{colorSelectorButtons}</div>;
}

export default ColorSelector;
