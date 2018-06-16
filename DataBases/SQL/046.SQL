SELECT t.ship, Classes.displacement, Classes.numGuns
FROM CLasses
RIGHT JOIN
(SELECT Outcomes.ship, Ships.class
FROM Outcomes
LEFT JOIN Ships ON Ships.name=Outcomes.ship
WHERE battle='Guadalcanal' AND Ships.class IS NOT NULL
UNION
SELECT Outcomes.ship, Outcomes.ship as class
FROM Outcomes
LEFT JOIN Ships ON Ships.name=Outcomes.ship
WHERE battle='Guadalcanal' AND Ships.class IS NULL) as t
ON t.class=Classes.class
