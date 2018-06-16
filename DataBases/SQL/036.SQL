SELECT name FROM Ships WHERE name = class
UNION
SELECT ship FROM Outcomes INNER JOIN Classes ON Outcomes.ship = Classes.class
