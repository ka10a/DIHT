SELECT maker, COUNT(type)
FROM Product
WHERE type = 'PC'
GROUP BY maker
HAVING COUNT(type) > 2
