WITH x AS(SELECT*FROM t)SELECT sum(1)""EXCEPT SELECT 0 ORDER BY 0 COLLATE"";

