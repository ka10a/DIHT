SELECT maker
FROM Product
INTERSECT (SELECT maker
FROM Product
INNER JOIN PC
ON PC.model = Product.model
WHERE speed >= 750)
INTERSECT (SELECT maker
FROM Product
INNER JOIN Laptop
ON Laptop.model = Product.model
WHERE speed >= 750)
