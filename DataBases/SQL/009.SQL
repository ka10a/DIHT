SELECT DISTINCT maker
FROM Product
INNER JOIN PC
ON Product.model = PC.model
WHERE type = 'PC' AND speed >= 450