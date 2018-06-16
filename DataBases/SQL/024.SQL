SELECT t1.model
FROM
(SELECT model, price FROM PC
UNION
SELECT model, price FROM Laptop
UNION
SELECT model, price FROM Printer) t1
WHERE t1.price =
(SELECT MAX(t2.price1) FROM
(SELECT MAX(price) AS price1 FROM PC
UNION
SELECT MAX(price) FROM Laptop
UNION
SELECT MAX(price) FROM Printer) t2)