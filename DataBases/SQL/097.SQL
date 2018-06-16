SELECT code, speed, ram, price, screen 
FROM Laptop
WHERE EXISTS(SELECT 1 x
FROM ( 
SELECT v, RANK() OVER(ORDER BY v) rn 
FROM (
SELECT CAST(speed AS FLOAT) AS sp, CAST(ram AS FLOAT) AS rm, 
CAST(price AS FLOAT) AS pr, CAST(screen AS FLOAT) AS sc 
)l UNPIVOT(v FOR c in (sp, rm, pr, sc))u 
)l PIVOT(MAX(v) FOR rn in ([1],[2],[3],[4]))p 
WHERE [1]*2 <= [2] AND [2]*2 <= [3] AND [3]*2 <= [4] 
)
