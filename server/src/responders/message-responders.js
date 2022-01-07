// @flow

import invariant from 'invariant';
import t from 'tcomb';

import { createMediaMessageData, trimMessage } from 'lib/shared/message-utils';
import { defaultNumberPerThread } from 'lib/types/message-types';
import {
  type SendTextMessageRequest,
  type SendMultimediaMessageRequest,
  type FetchMessageInfosResponse,
  type FetchMessageInfosRequest,
  type SendMessageResponse,
  sendMessageResponseValidator,
  fetchMessageInfosResponseValidator,
} from 'lib/types/message-types-api';
import { messageTypes } from 'lib/types/message-types-enum';
import type { TextMessageData } from 'lib/types/messages/text';
import { threadPermissions } from 'lib/types/thread-types';
import { ServerError } from 'lib/utils/errors';
import { tShape } from 'lib/utils/validation-utils';

import createMessages from '../creators/message-creator';
import {
  fetchMessageInfos,
  fetchMessageInfoForLocalID,
} from '../fetchers/message-fetchers';
import { checkThreadPermission } from '../fetchers/thread-permission-fetchers';
import { fetchMedia } from '../fetchers/upload-fetchers';
import type { Viewer } from '../session/viewer';
import { assignMedia } from '../updaters/upload-updaters';
import {
  validateInput,
  validateAndConvertOutput,
} from '../utils/validation-utils';

const sendTextMessageRequestInputValidator = tShape({
  threadID: t.String,
  localID: t.maybe(t.String),
  text: t.String,
});
async function textMessageCreationResponder(
  viewer: Viewer,
  input: any,
): Promise<SendMessageResponse> {
  const request: SendTextMessageRequest = input;
  await validateInput(viewer, sendTextMessageRequestInputValidator, request);

  const { threadID, localID, text: rawText } = request;
  const text = trimMessage(rawText);
  if (!text) {
    throw new ServerError('invalid_parameters');
  }

  const hasPermission = await checkThreadPermission(
    viewer,
    threadID,
    threadPermissions.VOICED,
  );
  if (!hasPermission) {
    throw new ServerError('invalid_parameters');
  }

  const messageData: TextMessageData = {
    type: messageTypes.TEXT,
    threadID,
    creatorID: viewer.id,
    time: Date.now(),
    text,
  };
  if (localID) {
    messageData.localID = localID;
  }
  const rawMessageInfos = await createMessages(viewer, [messageData]);
  const response = { newMessageInfo: rawMessageInfos[0] };
  return validateAndConvertOutput(
    viewer,
    sendMessageResponseValidator,
    response,
  );
}

const fetchMessageInfosRequestInputValidator = tShape({
  cursors: t.dict(t.String, t.maybe(t.String)),
  numberPerThread: t.maybe(t.Number),
});
async function messageFetchResponder(
  viewer: Viewer,
  input: any,
): Promise<FetchMessageInfosResponse> {
  const request: FetchMessageInfosRequest = input;
  await validateInput(viewer, fetchMessageInfosRequestInputValidator, request);
  const result = await fetchMessageInfos(
    viewer,
    { threadCursors: request.cursors },
    request.numberPerThread ? request.numberPerThread : defaultNumberPerThread,
  );
  const response = { ...result, userInfos: {} };
  return validateAndConvertOutput(
    viewer,
    fetchMessageInfosResponseValidator,
    response,
  );
}

const sendMultimediaMessageRequestInputValidator = tShape({
  threadID: t.String,
  localID: t.String,
  mediaIDs: t.list(t.String),
});
async function multimediaMessageCreationResponder(
  viewer: Viewer,
  input: any,
): Promise<SendMessageResponse> {
  const request: SendMultimediaMessageRequest = input;
  await validateInput(
    viewer,
    sendMultimediaMessageRequestInputValidator,
    request,
  );

  const { threadID, localID, mediaIDs } = request;
  if (mediaIDs.length === 0) {
    throw new ServerError('invalid_parameters');
  }

  const hasPermission = await checkThreadPermission(
    viewer,
    threadID,
    threadPermissions.VOICED,
  );
  if (!hasPermission) {
    throw new ServerError('invalid_parameters');
  }

  const [media, existingMessageInfo] = await Promise.all([
    fetchMedia(viewer, mediaIDs),
    fetchMessageInfoForLocalID(viewer, localID),
  ]);
  if (media.length !== mediaIDs.length && !existingMessageInfo) {
    throw new ServerError('invalid_parameters');
  }

  const messageData = createMediaMessageData({
    localID,
    threadID,
    creatorID: viewer.id,
    media,
  });
  const [newMessageInfo] = await createMessages(viewer, [messageData]);

  const { id } = newMessageInfo;
  invariant(
    id !== null && id !== undefined,
    'serverID should be set in createMessages result',
  );
  await assignMedia(viewer, mediaIDs, id);
  const response = { newMessageInfo };
  return validateAndConvertOutput(
    viewer,
    sendMessageResponseValidator,
    response,
  );
}

export {
  textMessageCreationResponder,
  messageFetchResponder,
  multimediaMessageCreationResponder,
};
