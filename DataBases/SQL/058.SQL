SELECT Ma.maker, Ty.type,
CAST(
CAST((SELECT COUNT(*) FROM Product WHERE type=Ty.type AND maker=Ma.maker)*100
AS NUMERIC(6, 2)
) / (SELECT COUNT(*) FROM Product WHERE maker=Ma.maker) AS NUMERIC(6, 2)
)
FROM (SELECT DISTINCT maker FROM Product) as Ma, (SELECT DISTINCT type from Product) AS Ty
