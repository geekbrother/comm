// @flow

import classNames from 'classnames';
import * as React from 'react';

import css from './modal.css';

export type ModalSize = 'small' | 'large';
type Props = {
  +name: string,
  +onClose: () => void,
  +children?: React.Node,
  +size?: ModalSize,
  +fixedHeight?: boolean,
};

function Modal(props: Props): React.Node {
  const { size = 'small', children, onClose, fixedHeight = true, name } = props;
  const overlayRef = React.useRef();

  const onBackgroundClick = React.useCallback(
    event => {
      if (event.target === overlayRef.current) {
        onClose();
      }
    },
    [onClose],
  );

  const onKeyDown = React.useCallback(
    event => {
      if (event.keyCode === 27) {
        onClose();
      }
    },
    [onClose],
  );

  React.useEffect(() => {
    if (overlayRef.current) {
      overlayRef.current.focus();
    }
  }, []);

  const overlayClasses = React.useMemo(
    () =>
      classNames(css['modal-overlay'], {
        [css['resizable-modal-overlay']]: !fixedHeight,
      }),
    [fixedHeight],
  );
  const modalContainerClasses = React.useMemo(
    () =>
      classNames(css['modal-container'], {
        [css['large-modal-container']]: size === 'large',
      }),
    [size],
  );
  const modalClasses = React.useMemo(
    () =>
      classNames(css['modal'], {
        [css['fixed-height-modal']]: fixedHeight,
      }),
    [fixedHeight],
  );
  return (
    <div
      className={overlayClasses}
      ref={overlayRef}
      onClick={onBackgroundClick}
      tabIndex={0}
      onKeyDown={onKeyDown}
    >
      <div className={modalContainerClasses}>
        <div className={modalClasses}>
          <div className={css['modal-header']}>
            <span className={css['modal-close']} onClick={onClose}>
              ×
            </span>
            <h2>{name}</h2>
          </div>
          {children}
        </div>
      </div>
    </div>
  );
}

export default Modal;
