WITH x AS(SELECT*FROM t)SELECT random()GLOB""EXCEPT SELECT 0 ORDER BY 1 COLLATE"";

