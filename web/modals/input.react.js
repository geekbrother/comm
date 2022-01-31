// @flow

import * as React from 'react';

type Props = React.ElementConfig<typeof ForwardedInput>;
import css from './input.css';

function Input(props: Props, ref): React.Node {
  const { label, id, ...rest } = props;
  return (
    <>
      {label && (
        <label className={css.label} htmlFor={id}>
          {label}
        </label>
      )}
      <input className={css.input} id={id} {...rest} ref={ref} />
    </>
  );
}

const ForwardedInput: React.AbstractComponent<
  Props,
  HTMLInputElement,
> = React.forwardRef<Props, HTMLInputElement>(Input);

export default ForwardedInput;
