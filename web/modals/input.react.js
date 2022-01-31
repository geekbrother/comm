// @flow

import * as React from 'react';

type Props = React.ElementConfig<typeof ForwardedInput>;

function Input(props: Props, ref): React.Node {
  return <input {...props} ref={ref} />;
}

const ForwardedInput: React.AbstractComponent<
  Props,
  HTMLInputElement,
> = React.forwardRef<Props, HTMLInputElement>(Input);

export default ForwardedInput;
