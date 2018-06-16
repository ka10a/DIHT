WITH t AS (SELECT SUM(CASE WHEN time_in > time_out THEN ABS(DATEDIFF(mi, time_in, time_out)) ELSE 24*60 - ABS(DATEDIFF(mi, time_in, time_out)) END) AS time, ID_comp, date
FROM (SELECT MAX(Trip.time_in) AS time_in, MAX(Trip.time_out) AS time_out, Trip.ID_comp, date
FROM Pass_in_trip AS PIT2 INNER JOIN Trip ON Trip.trip_no = PIT2.trip_no
GROUP BY PIT2.date, Trip.ID_comp, Trip.trip_no) as t1
GROUP BY date, ID_comp)

SELECT (SELECT name FROM Company WHERE ID_comp=t.ID_comp) AS Company, SUM(time) AS time
FROM t
GROUP BY ID_comp
