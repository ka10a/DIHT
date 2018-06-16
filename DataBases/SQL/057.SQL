WITH allships AS
(
SELECT Ships.name, Ships.class FROM Classes INNER JOIN Ships ON Ships.class=Classes.class
UNION
SELECT Outcomes.ship, Classes.class FROM CLasses INNER JOIN Outcomes ON Outcomes.ship=Classes.class
)

SELECT t.class, count(*) FROM
(SELECT class FROM allships GROUP BY class HAVING COUNT(*) > 2) as t
INNER JOIN allships ON t.class=allships.class
INNER JOIN Outcomes ON allships.name=Outcomes.ship
WHERE result='sunk'
GROUP BY t.class
