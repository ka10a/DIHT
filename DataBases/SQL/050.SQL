SELECT DISTINCT battle
FROM Outcomes
WHERE ship IN (SELECT name FROM Ships WHERE class='Kongo')
