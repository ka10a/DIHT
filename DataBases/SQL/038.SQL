SELECT  DISTINCT tc2.country
FROM Classes as tc2
GROUP BY country
HAVING 'bb' IN (SELECT type FROM Classes as tc3 WHERE tc3.country = tc2.country)
AND 'bc' IN (SELECT type FROM Classes as tc3 WHERE tc3.country = tc2.country)
