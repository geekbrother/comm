// @flow

import * as React from 'react';

import type { ThreadInfo } from 'lib/types/thread-types';

import Button from '../../components/button.react';
import Modal from '../modal.react';

type Props = {
  +onClose: () => void,
  +onConfirm: () => void,
  +threadInfo: ThreadInfo,
};

function SidebarPromoteModal(props: Props): React.Node {
  const { threadInfo, onClose, onConfirm } = props;
  const { uiName } = threadInfo;

  const handleConfirm = React.useCallback(() => {
    onConfirm();
    onClose();
  }, [onClose, onConfirm]);

  return (
    <Modal name="Promote Thread" icon="warning-circle" onClose={onClose}>
      <div>
        <p>{`Are you sure you want to promote "${uiName}"?
        "This promoting a sidebar to a full thread can't be undone."`}</p>

        <Button onClick={handleConfirm} type="submit" variant="danger">
          Promote to Full Thread
        </Button>
        <Button onClick={onConfirm} type="submit" variant="secondary">
          Cancel
        </Button>
      </div>
    </Modal>
  );
}

export default SidebarPromoteModal;
