WITH x AS(SELECT*FROM t)SELECT randomblob(1) -1""EXCEPT SELECT 0 ORDER BY 1 COLLATE"";

