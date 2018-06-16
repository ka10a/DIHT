SELECT AVG(price)
FROM
(SELECT price FROM PC
INNER JOIN Product ON PC.model = Product.model WHERE type='PC' and maker='A'
UNION all
SELECT price FROM Laptop
INNER JOIN Product ON Laptop.model = Product.model WHERE type='Laptop' and maker='A') as t1
