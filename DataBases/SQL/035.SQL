SELECT model, type
FROM Product
WHERE upper(model) NOT like '%[^A-Z]%' 
OR model not like '%[^0-9]%'
