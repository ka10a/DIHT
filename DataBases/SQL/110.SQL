WITH t AS (SELECT DISTINCT ID_psg
FROM Pass_in_trip AS PIT
INNER JOIN Trip ON PIT.trip_no=Trip.trip_no
WHERE Trip.time_out > Trip.time_in AND DATENAME(weekday, date) = 'Saturday')

SELECT (SELECT name FROM Passenger WHERE ID_psg = t.ID_psg) AS name
FROM t