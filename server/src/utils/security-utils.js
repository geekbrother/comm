// @flow

import type { $Request } from 'express';

import { getAppURLFacts, getNewAppURLFacts } from './urls';

const { basePath } = getNewAppURLFacts();

function assertSecureRequest(req: $Request) {
  const { https } = req.url.startsWith(basePath)
    ? getNewAppURLFacts()
    : getAppURLFacts();
  if (https && req.get('X-Forwarded-SSL') !== 'on') {
    throw new Error('insecure request');
  }
}

export { assertSecureRequest };
