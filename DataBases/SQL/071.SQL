SELECT t1.maker FROM Product AS t1
GROUP BY t1.maker
HAVING (SELECT COUNT(DISTINCT model) FROM Product AS t2 WHERE t1.maker=t2.maker AND type='PC') != 0 AND (SELECT COUNT(DISTINCT model) FROM Product AS t2 WHERE t1.maker=t2.maker AND type='PC') = (SELECT COUNT(DISTINCT PC.model) FROM PC INNER JOIN Product ON Product.model=PC.model WHERE Product.maker=t1.maker)
