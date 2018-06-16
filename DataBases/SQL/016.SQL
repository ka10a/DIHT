SELECT DISTINCT (SELECT MAX(pc3.model) FROM PC as pc3, PC as pc4 WHERE pc1.model = pc3.model or pc2.model = pc3.model),
(SELECT MIN(pc3.model) FROM PC as pc3, PC as pc4 WHERE pc1.model = pc3.model or pc2.model = pc3.model), pc1.speed, pc1.ram
FROM PC as pc1, PC as pc2
WHERE pc1.speed = pc2.speed and pc1.ram = pc2.ram and pc1.model != pc2.model
