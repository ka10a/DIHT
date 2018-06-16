SELECT DISTINCT maker
FROM Product
WHERE type='Printer'
AND maker IN
(SELECT maker FROM Product
INNER JOIN PC ON PC.model=product.model
WHERE
PC.ram = (SELECT MIN(t1.ram) FROM PC as t1)
AND
PC.speed = (SELECT MAX(t2.speed) FROM (SELECT * FROM PC WHERE PC.ram = (SELECT MIN(ram) FROM PC)) as t2))
