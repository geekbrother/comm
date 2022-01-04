// @flow

import { dbQuery, SQL } from './database';

const migrations: $ReadOnlyMap<number, () => Promise<void>> = new Map();

async function migrate(): Promise<boolean> {
  let dbVersion = null;
  try {
    await createDBVersionEntry();
    dbVersion = await getDBVersion();
    console.log(`(node:${process.pid}) DB version: ${dbVersion}`);
  } catch (err) {
    console.error(`(node:${process.pid}) ${err}`);
    return false;
  }

  for (const [idx, migration] of migrations.entries()) {
    if (idx <= dbVersion) {
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

async function createDBVersionEntry(): Promise<void> {
  const insertQuery = SQL`
    INSERT INTO metadata (name, data)
    VALUES ('db_version', 0)
    ON DUPLICATE KEY
    UPDATE
      name = name;
  `;
  await dbQuery(insertQuery);
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

async function updateDBVersion(dbVersion: number): Promise<void> {
  const updateQuery = SQL`
    UPDATE metadata
    SET data = ${dbVersion}
    WHERE name = 'db_version';
  `;
  await dbQuery(updateQuery);
}

async function beginTransaction(): Promise<void> {
  const beginTxnQuery = SQL`
        START TRANSACTION;
      `;
  await dbQuery(beginTxnQuery);
}

async function endTransaction(): Promise<void> {
  const endTxnQuery = SQL`
        COMMIT;
      `;
  await dbQuery(endTxnQuery);
}

async function rollbackTransaction(): Promise<void> {
  const rollbackTxnQuery = SQL`
        ROLLBACK;
      `;
  await dbQuery(rollbackTxnQuery);
}

export default migrate;
