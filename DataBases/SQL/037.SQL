SELECT class
FROM (SELECT class, name FROM ships
UNION
SELECT ship, ship FROM Outcomes) as t
GROUP BY t.class
HAVING COUNT(name) = 1 AND class IN (SELECT class FROM Classes)
