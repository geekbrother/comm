// @flow

import classNames from 'classnames';
import * as React from 'react';

import SWMansionIcon from '../SWMansionIcon.react';
import css from './modal.css';
export type ModalSize = 'small' | 'large' | 'fit-content';
type Props = {
  +name: React.Node,
  +onClose: () => void,
  +children?: React.Node,
  +size?: ModalSize,
};

function Modal(props: Props): React.Node {
  const { size = 'small', children, onClose, name: title } = props;
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

  const modalContainerClasses = React.useMemo(
    () =>
      classNames(css.modalContainer, {
        [css.modalContainerLarge]: size === 'large',
        [css.modalContainerSmall]: size === 'small',
      }),
    [size],
  );

  return (
    <div
      className={css.modalOverlay}
      ref={overlayRef}
      onClick={onBackgroundClick}
      tabIndex={0}
      onKeyDown={onKeyDown}
    >
      <div className={modalContainerClasses}>
        <div className={css.modalHeader}>
          <div className={css.title}>{title}</div>
          <div className={css.modalClose} onClick={onClose}>
            <SWMansionIcon icon="cross" size={24} />
          </div>
        </div>
        {children}
      </div>
    </div>
  );
}

export default Modal;
