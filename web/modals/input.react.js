// @flow

import * as React from 'react';

import css from './input.css';

type Props = {
  +type: string,
  +placeholder: string,
  +value: string,
  +onChange: (value: SyntheticEvent<HTMLInputElement>) => mixed,
  +disabled: boolean,
  +id?: string,
  +label?: string,
};

function Input(props: Props, ref): React.Node {
  const { type, placeholder, value, onChange, disabled, id, label } = props;
  return (
    <>
      {label && (
        <label className={css.label} htmlFor={id}>
          {label}
        </label>
      )}
      <input
        className={css.input}
        type={type}
        placeholder={placeholder}
        value={value}
        onChange={onChange}
        disabled={disabled}
        ref={ref}
        id={id}
      />
    </>
  );
}

const ForwardedInput: React.AbstractComponent<
  Props,
  HTMLInputElement,
> = React.forwardRef<Props, HTMLInputElement>(Input);

export default ForwardedInput;
