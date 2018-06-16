WITH t AS (SELECT country, MAX(ISNULL(numGuns, 0)) * 5000 AS numGuns, MAX(ISNULL(bore, 0)) * 3000 AS bore, MAX(ISNULL(displacement, 0)) AS disp FROM Classes GROUP BY country)

SELECT country, numGuns, 'numguns' FROM t
WHERE numGuns >= bore AND numGuns >= disp
UNION
SELECT country, bore, 'bore' FROM t
WHERE numGuns <= bore AND bore >= disp
UNION
SELECT country, disp, 'displacement' FROM t
WHERE disp >= bore AND numGuns <= disp