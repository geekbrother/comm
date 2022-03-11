// @flow

import commAppURLFacts from '../../facts/commapp_url';
import landingURLFacts from '../../facts/landing_url';
import squadCalURLFacts from '../../facts/squadcal_url';
import baseURLFacts from '../../facts/url';

type GlobalURLFacts = {
  +baseRoutePath: string,
};

function getGlobalURLFacts(): GlobalURLFacts {
  return baseURLFacts;
}

export type AppURLFacts = {
  +baseDomain: string,
  +basePath: string,
  +https: boolean,
};
type LandingURLFacts = {
  ...AppURLFacts,
  +baseRoutePath: string,
};

function getSquadCalURLFacts(): AppURLFacts {
  return squadCalURLFacts;
}

function getCommAppURLFacts(): AppURLFacts {
  return commAppURLFacts;
}

function getAppURLFactsFromRequestURL(url: string): AppURLFacts {
  return url.startsWith(getCommAppURLFacts().basePath)
    ? getCommAppURLFacts()
    : getSquadCalURLFacts();
}

function getLandingURLFacts(): LandingURLFacts {
  return landingURLFacts;
}

export {
  getGlobalURLFacts,
  getSquadCalURLFacts,
  getCommAppURLFacts,
  getLandingURLFacts,
  getAppURLFactsFromRequestURL,
};
