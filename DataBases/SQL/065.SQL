SELECT ROW_NUMBER() OVER(ORDER BY maker, CASE WHEN type='PC' THEN 1 WHEN type='Laptop' THEN 2 ELSE 3 END) Num,
CASE WHEN type='PC' THEN maker
WHEN type='Laptop' THEN CASE WHEN maker IN (SELECT maker FROM Product WHERE type='PC') THEN '' ELSE maker END
ELSE CASE WHEN maker IN (SELECT maker FROM Product WHERE type='PC' OR type='Laptop') THEN '' ELSE maker END END maker,
type
FROM Product
GROUP BY maker, type
