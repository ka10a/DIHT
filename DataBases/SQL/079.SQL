WITH t AS (SELECT ID_psg, Trip.trip_no, SUM(CASE WHEN Trip.time_out > Trip.time_in THEN 24*60 - ABS(DATEDIFF(mi, Trip.time_in, Trip.time_out)) ELSE ABS(DATEDIFF (mi, Trip.time_in, time_out)) END) as time
FROM Pass_in_trip AS PIT
INNER JOIN Trip ON Trip.trip_no=PIT.trip_no
GROUP BY ID_psg, Trip.trip_no)

SELECT (SELECT name FROM Passenger AS P WHERE P.ID_psg=t.ID_psg) AS name, SUM(time) AS minutes
FROM t
GROUP BY ID_psg
HAVING SUM(time) >= ALL (SELECT SUM(time) FROM t GROUP BY ID_psg)
