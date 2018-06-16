WITH t AS
(
SELECT class, COUNT(*) as cnt FROM
(
SELECT class, ship, result FROM Classes INNER JOIN Outcomes ON Outcomes.ship=Classes.class
UNION 
SELECT Classes.class, ship, result FROM (Classes
INNER JOIN Ships ON Ships.class=Classes.class
INNER JOIN Outcomes ON Ships.name=Outcomes.ship)
) as t1
WHERE result='sunk'
GROUP BY class
)

SELECT * FROM t
UNION
SELECT class, 0 FROM CLasses
WHERE class NOT IN (SELECT t.class FROM t)
