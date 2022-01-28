// @flow

import * as React from 'react';

import css from './input.css';

type Props = {
  +type: string,
  +placeholder: string,
  +value: string,
  +onChange: (value: string) => mixed,
  +disabled: boolean,
};

function Input(props: Props, ref): React.Node {
  const { type, placeholder, value, onChange, disabled } = props;
  return (
    <input
      className={css.input}
      type={type}
      placeholder={placeholder}
      value={value}
      onChange={onChange}
      disabled={disabled}
      ref={ref}
    />
  );
}

const ForwardedInput: React.AbstractComponent<
  Props,
  HTMLInputElement,
> = React.forwardRef<Props, HTMLInputElement>(Input);

export default ForwardedInput;
