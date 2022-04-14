// @flow

import classNames from 'classnames';
import * as React from 'react';

import SWMansionIcon, { type Icon } from '../SWMansionIcon.react';
import css from './modal.css';

export type ModalSize = 'small' | 'large' | 'fit-content';
export type ModalProps = {
  +name: string,
  +icon?: Icon,
  +onClose: () => void,
  +children?: React.Node,
  +size?: ModalSize,
};

function Modal(props: ModalProps): React.Node {
  const { size = 'small', children, onClose, name, icon } = props;
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
  const headerIcon = React.useMemo(() => {
    if (!icon) {
      return null;
    }
    return <SWMansionIcon size={24} icon={icon} />;
  }, [icon]);

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
          <h2 className={css.title}>
            {headerIcon}
            {name}
          </h2>
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
