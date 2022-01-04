// @flow

import type { QueryResults } from 'mysql';

import { dbQuery, SQL } from './database';

const migrations: $ReadOnlyMap<number, () => Promise<void>> = new Map();

async function migrate(): Promise<boolean> {
  try {
    await createDBVersionEntry();
    var DBVersion = await getDBVersion();
    console.log(`(node:${process.pid}) DB version: ${DBVersion}`);
  } catch (err) {
    console.error(`(node:${process.pid}) ${err}`);
    return false;
  }

  for (const [idx, migration] of migrations.entries()) {
    if (idx <= DBVersion) {
      continue;
    }

    try {
      await beginTransaction();
      await migration();
      await updateDBVersion(idx);
      await endTransaction();
      console.log(`(node:${process.pid}) migration ${idx} succeeded.`);
    } catch (err) {
      console.error(`(node:${process.pid}) migration ${idx} failed.`);
      console.error(err);
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
  const DBVersion = versionResult.data;
  return DBVersion;
}

async function updateDBVersion(DBVersion: number): Promise<QueryResults> {
  const updateQuery = SQL`
    UPDATE metadata
    SET data = ${DBVersion}
    WHERE name = 'db_version';
  `;
  return dbQuery(updateQuery);
}

async function beginTransaction(): Promise<QueryResults> {
  const beginTxnQuery = SQL`
        START TRANSACTION;
      `;
  return dbQuery(beginTxnQuery);
}

async function endTransaction(): Promise<QueryResults> {
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

export default migrate;
