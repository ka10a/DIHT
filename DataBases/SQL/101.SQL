WITH t AS (SELECT *, 
CASE
WHEN color='n' THEN 1
ELSE 0
END + (SELECT COUNT(color) FROM Printer WHERE code < Pr.code AND color = 'n') AS G
FROM Printer AS Pr)

SELECT code, 
model, 
color, 
type, 
price, 
(SELECT MAX(model) FROM t WHERE G=t1.G) AS max_model, 
(SELECT COUNT(DISTINCT type) FROM t WHERE G=t1.G) AS distct_types, 
(SELECT AVG(price) FROM t WHERE G=t1.G) AS avg_price
FROM t AS t1