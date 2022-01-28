// @flow

import olmConfig from '../../secrets/olm_config.json';

type OlmConfig = {
  +privateKey: string,
};

function getOlmConfig(): OlmConfig {
  return olmConfig;
}

export { getOlmConfig };
