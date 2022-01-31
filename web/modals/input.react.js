// @flow

import * as React from 'react';

type Props = React.ElementConfig<typeof ForwardedInput>;

function Input(props: Props, ref): React.Node {
  const { label, id, ...rest } = props;
  return (
    <>
      {label && <label htmlFor={id}>{label}</label>}
      <input id={id} {...rest} ref={ref} />
    </>
  );
}

const ForwardedInput: React.AbstractComponent<
  Props,
  HTMLInputElement,
> = React.forwardRef<Props, HTMLInputElement>(Input);

export default ForwardedInput;
