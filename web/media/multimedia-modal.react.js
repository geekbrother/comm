// @flow

import invariant from 'invariant';
import * as React from 'react';
import { XCircle as XCircleIcon } from 'react-feather';

import { useModalContext } from '../modals/modal-provider.react';
import css from './media.css';

type BaseProps = {
  +uri: string,
};

type Props = {
  ...BaseProps,
  +onClose: (modal: ?React.Node) => void,
};

class MultimediaModal extends React.PureComponent<Props> {
  overlay: ?HTMLDivElement;

  componentDidMount() {
    invariant(this.overlay, 'overlay ref unset');
    this.overlay.focus();
  }

  render(): React.Node {
    return (
      <div
        className={css.multimediaModalOverlay}
        ref={this.overlayRef}
        onClick={this.onBackgroundClick}
        tabIndex={0}
        onKeyDown={this.onKeyDown}
      >
        <img src={this.props.uri} />
        <XCircleIcon
          onClick={this.props.onClose}
          className={css.closeMultimediaModal}
        />
      </div>
    );
  }

  overlayRef: (overlay: ?HTMLDivElement) => void = overlay => {
    this.overlay = overlay;
  };

  onBackgroundClick: (
    event: SyntheticEvent<HTMLDivElement>,
  ) => void = event => {
    if (event.target === this.overlay) {
      this.props.onClose();
    }
  };

  onKeyDown: (
    event: SyntheticKeyboardEvent<HTMLDivElement>,
  ) => void = event => {
    if (event.keyCode === 27) {
      this.props.onClose();
    }
  };
}

function ConnectedMultiMediaModal(props: BaseProps): React.Node {
  const modalContext = useModalContext();

  return <MultimediaModal {...props} onClose={modalContext.clearModal} />;
}

export default ConnectedMultiMediaModal;
