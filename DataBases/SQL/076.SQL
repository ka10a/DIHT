WITH t AS (SELECT ID_psg  FROM Pass_in_trip AS PIT GROUP BY PIT.ID_psg HAVING COUNT(DISTINCT PIT.place) = COUNT(PIT.place))

SELECT (SELECT name FROM Passenger AS P WHERE P.ID_psg=t.ID_psg) AS name,
(SELECT SUM(CASE 
WHEN Trip.time_out > Trip.time_in THEN 24*60 - ABS(DATEDIFF(mi, Trip.time_in, Trip.time_out))
ELSE ABS(DATEDIFF (mi, Trip.time_in, time_out)) 
END)) AS minutes FROM t
INNER JOIN Pass_in_trip ON t.ID_psg = Pass_in_trip.ID_psg
INNER JOIN Trip ON Trip.trip_no = Pass_in_trip.trip_no
GROUP BY t.ID_psg
