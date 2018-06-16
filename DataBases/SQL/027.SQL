SELECT DISTINCT maker, AVG(hd)
FROM Product
INNER JOIN pc
ON Product.model = pc.model
GROUP BY maker
HAVING maker IN (SELECT DISTINCT maker FROM Product WHERE type='Printer')
