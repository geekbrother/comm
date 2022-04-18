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

  return (
    <Modal name="Confirm leave thread" onClose={onClose}>
      <div>
        <p>{`Are you sure you want to leave "${uiName}"?`}</p>
        <Button onClick={onConfirm} type="submit" variant="danger">
          Leave Thread
        </Button>
      </div>
    </Modal>
  );
}

export default SidebarPromoteModal;
