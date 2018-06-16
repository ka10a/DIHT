SELECT fields,A FROM 
(SELECT cast(model as NVARCHAR(10)) as model,
cast (speed as NVARCHAR(10)) as speed,
cast(ram as NVARCHAR(10)) as ram,
cast(hd as NVARCHAR(10)) as hd,
cast(cd as NVARCHAR(10)) as cd,
cast(price as NVARCHAR(10)) as price FROM PC 
WHERE code = (SELECT MAX(code) FROM PC)) AS t 

UNPIVOT (A for fields in (model, speed, ram, hd, cd, price)) AS unpvt