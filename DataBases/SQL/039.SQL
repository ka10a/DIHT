SELECT DISTINCT t1.ship
FROM Outcomes as t1
WHERE t1.result='damaged'
AND t1.ship IN (SELECT t2.ship FROM Outcomes as t2
INNER JOIN Battles ON Battles.name = t2.battle
WHERE date > (SELECT b1.date FROM Battles as b1 WHERE b1.name = t1.battle))
