SELECT Ships.class, name, country
FROM Ships
INNER JOIN Classes ON Classes.class = Ships.class
WHERE numGuns >= 10
