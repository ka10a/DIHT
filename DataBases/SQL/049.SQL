SELECT name
FROM Ships
INNER JOIN CLasses on Ships.class=Classes.class
WHERE bore=16
UNION
SELECT ship
FROM Outcomes
INNER JOIN CLasses on Outcomes.ship=Classes.class
WHERE bore=16
