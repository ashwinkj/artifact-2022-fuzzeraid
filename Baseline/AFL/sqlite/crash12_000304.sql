WITH x AS(SELECT*FROM t)SELECT ifnull(1, .11)""EXCEPT SELECT 0 ORDER BY 1 COLLATE"";
