SELECT speed, avg(price)
FROM PC
GROUB BY speed
HAVING speed > 600
