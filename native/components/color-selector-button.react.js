// @flow

import * as React from 'react';
import { View, StyleSheet } from 'react-native';

type ColorSelectorButtonProps = {
  color: string,
};

function ColorSelectorButton(props: ColorSelectorButtonProps): React.Node {
  const { color } = props;
  const buttonBackgroundColor = React.useMemo(() => {
    return { backgroundColor: color };
  }, [color]);
  return <View style={[styles.button, buttonBackgroundColor]} />;
}

const styles = StyleSheet.create({
  button: {
    borderRadius: 100,
    height: 40,
    margin: 15,
    width: 40,
  },
});

export default ColorSelectorButton;
