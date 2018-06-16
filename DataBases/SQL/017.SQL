SELECT DISTINCT Product.type, Laptop.model, Laptop.speed
FROM Laptop
INNER JOIN Product
ON Product.model = Laptop.model
WHERE Laptop.speed < (SELECT MIN(PC.speed) FROM PC) AND Product.type='Laptop'
