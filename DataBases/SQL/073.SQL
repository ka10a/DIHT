WITH t AS (SELECT country, battle
FROM Outcomes INNER JOIN Classes ON Classes.class=Outcomes.ship
UNION
SELECT country, battle FROM Outcomes
INNER JOIN Ships ON Ships.name=Outcomes.ship
INNER JOIN Classes ON Ships.class=Classes.class)

SELECT DISTINCT country, name FROM Classes, Battles
WHERE country NOT IN (SELECT t.country FROM t WHERE t.country=country AND t.battle=name)
