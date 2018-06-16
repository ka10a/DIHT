SELECT DISTINCT maker, 
(CASE
WHEN (SELECT COUNT(DISTINCT type) FROM Product AS P1 WHERE P1.maker=P.maker) > 2 THEN 'Laptop/PC/Printer'
WHEN (SELECT COUNT(DISTINCT type) FROM Product AS P1 WHERE P1.maker=P.maker) < 2 THEN (SELECT MIN(type) FROM Product AS P1 WHERE P1.maker=P.maker)
ELSE
(CASE
WHEN 'Laptop' NOT IN (SELECT type FROM Product AS P1 WHERE P1.maker=P.maker) THEN 'PC/Printer'
WHEN 'PC' NOT IN (SELECT type FROM Product AS P1 WHERE P1.maker=P.maker) THEN 'Laptop/Printer'
ELSE 'Laptop/PC'
END)
END) as types
FROM Product AS P
GROUP BY P.maker
