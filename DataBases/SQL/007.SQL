SELECT Product.model, price
FROM Product
INNER JOIN PC
ON Product.model = PC.model
WHERE Product.type = 'PC' AND Product.maker = 'B'
UNION
SELECT Product.model, price
FROM Product
INNER JOIN Laptop
ON Product.model = Laptop.model
WHERE Product.type = 'Laptop' AND Product.maker = 'B'
UNION
SELECT Product.model, price
FROM Product
INNER JOIN Printer
ON Product.model = Printer.model
WHERE Product.type = 'Printer' AND Product.maker = 'B'
