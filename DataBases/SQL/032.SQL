SELECT country, CAST(AVG((POWER(bore,3)/2)) as NUMERIC(6,2)) as weight 
FROM
(SELECT country, bore, name  FROM Classes
LEFT JOIN Ships
ON classes.class = ships.class
UNION ALL
SELECT DISTINCT country, bore, ship FROM Classes
LEFT JOIN Outcomes
On classes.class = outcomes.ship
where ship not in (select name from ships)) as t
WHERE name IS NOT NULL
GROUP BY country
