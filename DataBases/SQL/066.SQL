WITH Weekdays AS (SELECT DATEADD(day, a, '2003-04-01') AS day
FROM (SELECT 0 AS a UNION SELECT 1 UNION SELECT 2 UNION SELECT 3 UNION SELECT 4 UNION SELECT 5 UNION SELECT 6) AS t)

SELECT day, CASE WHEN ans IS NULL THEN 0 ELSE ans END
FROM Weekdays LEFT JOIN
(
SELECT date, COUNT(DISTINCT Trip.trip_no) AS ans FROM Pass_in_trip AS Patr LEFT JOIN Trip ON Trip.trip_no=Patr.trip_no
WHERE town_from='Rostov' AND (date >= '2003-04-01' AND date <'2003-04-08')
GROUP BY date
) as t ON Weekdays.day=t.date
