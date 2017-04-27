// @flow

import type { Store } from 'redux';
import type { NavInfo, AppState, Action } from './redux-setup';

import invariant from 'invariant';
import { createSelector } from 'reselect';

import { infoFromURL } from 'lib/utils/url-utils';
import {
  yearAssertingExtractor,
  yearAssertingSelector,
  monthAssertingExtractor,
  monthAssertingSelector,
} from './selectors/nav-selectors';
import {
  startDateForYearAndMonth,
  endDateForYearAndMonth,
} from 'lib/utils/date-utils';

function urlForYearAndMonth(year: number, month: number) {
  return `year/${year}/month/${month}/`;
}

const monthURL = createSelector(
  yearAssertingSelector,
  monthAssertingSelector,
  (year: number, month: number) => urlForYearAndMonth(year, month),
);

function urlForHomeAndCalendarID(home: bool, calendarID: ?string) {
  if (home) {
    return "home/";
  }
  invariant(calendarID, "either home or calendarID should be set");
  return `calendar/${calendarID}/`;
}

const thisNavURLFragment = createSelector(
  (state: AppState) => state.navInfo,
  (navInfo: NavInfo) => urlForHomeAndCalendarID(
    navInfo.home,
    navInfo.calendarID
  ),
);

const thisURL = createSelector(
  monthURL,
  thisNavURLFragment,
  (monthURL: string, thisNavURLFragment: string) =>
    thisNavURLFragment + monthURL,
);

function canonicalURLFromReduxState(navInfo: NavInfo, currentURL: string) {
  const urlInfo = infoFromURL(currentURL);
  let newURL = `/${urlForHomeAndCalendarID(navInfo.home, navInfo.calendarID)}`;

  if (urlInfo.year !== undefined) {
    const year = yearAssertingExtractor(navInfo.startDate, navInfo.endDate);
    newURL += `year/${year}/`;
  }
  if (urlInfo.month !== undefined) {
    const month = monthAssertingExtractor(navInfo.startDate, navInfo.endDate);
    newURL += `month/${month}/`;
  }
  if (navInfo.verify) {
    newURL += `verify/${navInfo.verify}/`;
  }
  return newURL;
}

// Given a URL, this function parses out a navInfo object, leaving values as
// default if they are unspecified. 
function navInfoFromURL(url: string): NavInfo {
  const urlInfo = infoFromURL(url);
  const today = new Date();
  const year = urlInfo.year ? urlInfo.year : today.getFullYear();
  const month = urlInfo.month ? urlInfo.month : (today.getMonth() + 1);
  return {
    startDate: startDateForYearAndMonth(year, month),
    endDate: endDateForYearAndMonth(year, month),
    home: !!urlInfo.home,
    calendarID: urlInfo.calendarID ? urlInfo.calendarID : null,
    verify: urlInfo.verify ? urlInfo.verify : null,
  };
}

export {
  urlForYearAndMonth,
  monthURL,
  urlForHomeAndCalendarID,
  thisNavURLFragment,
  thisURL,
  canonicalURLFromReduxState,
  navInfoFromURL,
};
