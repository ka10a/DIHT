SELECT DISTINCT class
FROM Ships
WHERE name IN (SELECT ship FROM Outcomes WHERE result='sunk')
UNION
SELECT DISTINCT class
FROM Classes
WHERE class IN (SELECT ship FROM Outcomes WHERE result='sunk')
