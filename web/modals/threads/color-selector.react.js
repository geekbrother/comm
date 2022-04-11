// @flow

import * as React from 'react';

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
      <div className={css.row}>
        <ColorSelectorButton
          color="4B87AA"
          currentThreadColor={currentThreadColor}
          onColorSelection={onColorSelection}
        />
        <ColorSelectorButton
          color="5C9F5F"
          currentThreadColor={currentThreadColor}
          onColorSelection={onColorSelection}
        />
        <ColorSelectorButton
          color="B8753D"
          currentThreadColor={currentThreadColor}
          onColorSelection={onColorSelection}
        />
        <ColorSelectorButton
          color="AA4B4B"
          currentThreadColor={currentThreadColor}
          onColorSelection={onColorSelection}
        />
        <ColorSelectorButton
          color="6D49AB"
          currentThreadColor={currentThreadColor}
          onColorSelection={onColorSelection}
        />
      </div>
      <div className={css.row}>
        <ColorSelectorButton
          color="C85000"
          currentThreadColor={currentThreadColor}
          onColorSelection={onColorSelection}
        />
        <ColorSelectorButton
          color="008F83"
          currentThreadColor={currentThreadColor}
          onColorSelection={onColorSelection}
        />
        <ColorSelectorButton
          color="648CAA"
          currentThreadColor={currentThreadColor}
          onColorSelection={onColorSelection}
        />
        <ColorSelectorButton
          color="57697F"
          currentThreadColor={currentThreadColor}
          onColorSelection={onColorSelection}
        />
        <ColorSelectorButton
          color="575757"
          currentThreadColor={currentThreadColor}
          onColorSelection={onColorSelection}
        />
      </div>
    </div>
  );
}

export default ColorSelector;
