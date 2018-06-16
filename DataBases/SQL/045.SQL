SELECT Ships.name
FROM Ships
WHERE name LIKE '% % %'
UNION
SELECT Outcomes.ship
FROM Outcomes
WHERE ship LIKE '% % %'