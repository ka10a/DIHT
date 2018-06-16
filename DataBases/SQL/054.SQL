SELECT CAST(AVG(CAST(t.numGuns AS NUMERIC(6, 2))) AS NUMERIC(6, 2))
FROM
(SELECT name, numGuns FROM Ships
INNER JOIN Classes ON Ships.class=Classes.class
WHERE type='bb'
UNION
SELECT ship, numGuns FROM Outcomes
INNER JOIN Classes ON Outcomes.ship=Classes.class
WHERE type='bb') as t
