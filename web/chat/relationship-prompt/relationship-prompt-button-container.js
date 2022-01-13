// @flow

import * as React from 'react';

import css from './relationship-prompt.css';

type Props = { +children: any };

function RelationshipPromptButtonContainer(props: Props): React.Node {
  const { children } = props;
  return <div className={css.promptButtonContainer}>{children}</div>;
}

export default RelationshipPromptButtonContainer;
