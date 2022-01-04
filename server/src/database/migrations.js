// @flow

import type { QueryResults } from 'mysql';

import { getMessageForException } from 'lib/utils/errors';

import { dbQuery, SQL } from './database';

const migrations: $ReadOnlyMap<number, () => Promise<void>> = new Map();

async function migrate(): Promise<boolean> {
  let dbVersion = null;
  try {
    await createDBVersionEntry();
    dbVersion = await getDBVersion();
    console.log(`(node:${process.pid}) DB version: ${dbVersion}`);
  } catch (e) {
    const dbVersionExceptionMessage = String(getMessageForException(e));
    console.error(`(node:${process.pid}) ${dbVersionExceptionMessage}`);
    return false;
  }

  for (const [idx, migration] of migrations.entries()) {
    if (idx < dbVersion) {
      continue;
    }

    try {
      await startTransaction();
      await migration();
      await updateDBVersion(idx);
      await commitTransaction();
      console.log(`(node:${process.pid}) migration ${idx} succeeded.`);
    } catch (e) {
      const transactionExceptionMessage = String(getMessageForException(e));
      console.error(`(node:${process.pid}) migration ${idx} failed.`);
      console.error(transactionExceptionMessage);
      await rollbackTransaction();
      return false;
    }
  }
  return true;
}

async function createDBVersionEntry(): Promise<QueryResults> {
  const insertQuery = SQL`
    INSERT INTO metadata (name, data)
    VALUES ('db_version', 0)
    ON DUPLICATE KEY
    UPDATE
      name = name;
  `;
  return dbQuery(insertQuery);
}

async function getDBVersion(): Promise<number> {
  const versionQuery = SQL`
    SELECT data
    FROM metadata
    WHERE name = 'db_version';
  `;
  const [[versionResult]] = await dbQuery(versionQuery);
  const dbVersion = versionResult.data;
  return dbVersion;
}

async function updateDBVersion(dbVersion: number): Promise<QueryResults> {
  const updateQuery = SQL`
    UPDATE metadata
    SET data = ${dbVersion}
    WHERE name = 'db_version';
  `;
  return dbQuery(updateQuery);
}

async function startTransaction(): Promise<QueryResults> {
  const beginTxnQuery = SQL`
        START TRANSACTION;
      `;
  return dbQuery(beginTxnQuery);
}

async function commitTransaction(): Promise<QueryResults> {
  const endTxnQuery = SQL`
        COMMIT;
      `;
  return dbQuery(endTxnQuery);
}

async function rollbackTransaction(): Promise<QueryResults> {
  const rollbackTxnQuery = SQL`
        ROLLBACK;
      `;
  return dbQuery(rollbackTxnQuery);
}

export { migrate };
