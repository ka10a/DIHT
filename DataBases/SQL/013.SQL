SELECT AVG(speed)
FROM PC
INNER JOIN Product
ON PC.model = Product.model
WHERE type = 'PC' AND maker = 'A'
