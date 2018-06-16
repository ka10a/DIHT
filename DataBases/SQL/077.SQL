WITH t AS (SELECT COUNT(DISTINCT Trip.trip_no) AS tr_no, date
FROM Pass_in_trip AS PIT
INNER JOIN Trip ON Trip.trip_no=PIT.trip_no
WHERE town_from='Rostov'
GROUP BY town_from, PIT.date)

SELECT tr_no, date FROM t
WHERE tr_no >= ALL (SELECT tr_no FROM t)
