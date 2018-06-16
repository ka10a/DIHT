SELECT DISTINCT battle FROM 
(SELECT battle, country, ship FROM Outcomes
INNER JOIN Ships ON Ships.name=Outcomes.ship
INNER JOIN Classes On Classes.class=Ships.class
UNION
SELECT battle, country, ship FROM Outcomes
INNER JOIN Classes On Classes.class=Outcomes.ship) AS t
GROUP BY t.battle, t.country
HAVING COUNT(*) >= 3
