// @flow

import classNames from 'classnames';
import * as React from 'react';

import css from './color-selector-button.css';

type ColorSelectorButtonProps = {
  +color: string,
  +pendingColorSelection: string,
  +setPendingColorSelection: string => void,
};
function ColorSelectorButton(props: ColorSelectorButtonProps): React.Node {
  const { color, pendingColorSelection, setPendingColorSelection } = props;

  const active = React.useMemo(() => color === pendingColorSelection, [
    color,
    pendingColorSelection,
  ]);

  const containerClassName = classNames(css.container, {
    [css.active]: active,
  });

  const colorSplotchStyle = React.useMemo(
    () => ({
      backgroundColor: color,
    }),
    [color],
  );

  const onColorSplotchClicked = React.useCallback(() => {
    setPendingColorSelection(color);
  }, [setPendingColorSelection, color]);

  return (
    <div onClick={onColorSplotchClicked} className={containerClassName}>
      <div className={css.colorSplotch} style={colorSplotchStyle} />
    </div>
  );
}

export default ColorSelectorButton;
