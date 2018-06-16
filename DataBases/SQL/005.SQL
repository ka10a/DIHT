SELECT model, speed, hd
FROM PC
WHERE (PC.cd = '12x' OR PC.cd = '24x') and PC.price < 600
