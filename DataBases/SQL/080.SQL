WITH t AS (SELECT DISTINCT maker FROM Product
LEFT JOIN PC ON Product.model=PC.model
WHERE type='PC' AND PC.model IS NULL)

SELECT  DISTINCT maker FROM Product
WHERE maker NOT IN (SELECT * FROM t)
