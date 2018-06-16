SELECT maker, model, ROW_NUMBER() OVER(ORDER BY maker, model) AS A,
(SELECT q
FROM (SELECT ROW_NUMBER() OVER(ORDER BY maker) AS q, maker
FROM Product GROUP BY maker) AS t1
WHERE maker = P.maker) AS B,
(SELECT MIN(q)
FROM (SELECT ROW_NUMBER() OVER(ORDER BY maker, model) AS q, maker
FROM Product) AS t2
WHERE maker = P.maker) AS C,
(SELECT MAX(q)
FROM (SELECT ROW_NUMBER() OVER(ORDER BY maker, model) AS q, maker
FROM Product) AS t3
WHERE maker = P.maker) AS D
FROM Product AS P
