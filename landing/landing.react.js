// @flow

import * as React from 'react';
import { useRouteMatch, useLocation } from 'react-router-dom';

import AppLanding from './app-landing.react';
import Footer from './footer.react';
import Header from './header.react';
import Keyservers from './keyservers.react';
import Privacy from './privacy.react';
import Support from './support.react';
import Terms from './terms.react';
import useScrollToTopOnNavigate from './use-scroll-to-top-on-navigate.react';
import './shared.css';

function Landing(): React.Node {
  useScrollToTopOnNavigate();
  const { pathname } = useLocation();
  const onPrivacy = useRouteMatch({ path: '/privacy' });
  const onTerms = useRouteMatch({ path: '/terms' });
  const onSupport = useRouteMatch({ path: '/support' });
  const onKeyservers = useRouteMatch({ path: '/keyservers' });
  const isLegalPage: boolean = React.useMemo(
    () => !!(onPrivacy || onTerms || onSupport),
    [onPrivacy, onSupport, onTerms],
  );

  const onRequestAccess = React.useCallback(async (e: Event) => {
    e.preventDefault();
    window?.scrollTo(0, document.body?.scrollHeight);
    document.getElementById('subscription-form')?.focus();
  }, []);

  const activePage = React.useMemo(() => {
    if (onPrivacy) {
      return <Privacy />;
    } else if (onTerms) {
      return <Terms />;
    } else if (onSupport) {
      return <Support />;
    } else if (onKeyservers) {
      return <Keyservers />;
    } else {
      return <AppLanding {...{ onRequestAccess }} />;
    }
  }, [onKeyservers, onPrivacy, onSupport, onTerms, onRequestAccess]);

  return (
    <div>
      <Header {...{ pathname, isLegalPage, onRequestAccess }} />
      {activePage}
      <Footer {...{ pathname, isLegalPage }} />
    </div>
  );
}

export default Landing;
