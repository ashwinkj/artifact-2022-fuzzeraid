CREATE TABLE t0(z);SAVEPOINT
VACUUM;WITH d(x)AS(SELECT*UNION SELECT 0)INSERT INTO t0 SELECT 0 FROM d;

