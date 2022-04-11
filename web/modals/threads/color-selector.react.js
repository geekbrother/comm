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

  return (
    <div className={css.container}>
      <ColorSelectorButton
        color={selectedThreadColors[0]}
        currentThreadColor={currentThreadColor}
        onColorSelection={onColorSelection}
      />
      <ColorSelectorButton
        color={selectedThreadColors[1]}
        currentThreadColor={currentThreadColor}
        onColorSelection={onColorSelection}
      />
      <ColorSelectorButton
        color={selectedThreadColors[2]}
        currentThreadColor={currentThreadColor}
        onColorSelection={onColorSelection}
      />
      <ColorSelectorButton
        color={selectedThreadColors[3]}
        currentThreadColor={currentThreadColor}
        onColorSelection={onColorSelection}
      />
      <ColorSelectorButton
        color={selectedThreadColors[4]}
        currentThreadColor={currentThreadColor}
        onColorSelection={onColorSelection}
      />
      <ColorSelectorButton
        color={selectedThreadColors[5]}
        currentThreadColor={currentThreadColor}
        onColorSelection={onColorSelection}
      />
      <ColorSelectorButton
        color={selectedThreadColors[6]}
        currentThreadColor={currentThreadColor}
        onColorSelection={onColorSelection}
      />
      <ColorSelectorButton
        color={selectedThreadColors[7]}
        currentThreadColor={currentThreadColor}
        onColorSelection={onColorSelection}
      />
      <ColorSelectorButton
        color={selectedThreadColors[8]}
        currentThreadColor={currentThreadColor}
        onColorSelection={onColorSelection}
      />
      <ColorSelectorButton
        color={selectedThreadColors[9]}
        currentThreadColor={currentThreadColor}
        onColorSelection={onColorSelection}
      />
    </div>
  );
}

export default ColorSelector;
