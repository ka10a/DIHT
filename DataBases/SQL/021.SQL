SELECT maker, max(price)
FROM PC
INNER JOIN Product ON (PC.model=Product.model AND Product.type='PC')
GROUP BY maker
