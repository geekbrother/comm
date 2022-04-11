// @flow

import classNames from 'classnames';
import * as React from 'react';
import tinycolor from 'tinycolor2';

import css from './color-selector-button.css';

type ColorSelectorButtonProps = {
  +color: string,
  +currentThreadColor: string,
  +onColorSelection: (hex: string) => void,
};
function ColorSelectorButton(props: ColorSelectorButtonProps): React.Node {
  const { color, currentThreadColor, onColorSelection } = props;

  const active = tinycolor.equals(color, currentThreadColor);
  const containerClassName = classNames(css.container, {
    [css.active]: active,
  });

  const colorSplotchStyle = React.useMemo(
    () => ({
      backgroundColor: `#${color}`,
    }),
    [color],
  );

  const onColorSplotchClicked = React.useCallback(() => {
    onColorSelection(color);
  }, [onColorSelection, color]);

  return (
    <div onClick={onColorSplotchClicked} className={containerClassName}>
      <div className={css.colorSplotch} style={colorSplotchStyle} />
    </div>
  );
}

export default ColorSelectorButton;
