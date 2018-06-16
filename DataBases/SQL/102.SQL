WITH t AS (SELECT ID_psg, town_from FROM Pass_in_trip AS PIT
INNER JOIN Trip ON PIT.trip_no=Trip.trip_no)

SELECT (SELECT name FROM Passenger AS P WHERE P.ID_psg=t3.ID_psg) AS name
FROM (
SELECT * FROM t
UNION
SELECT ID_psg, town_to FROM Pass_in_trip AS PIT
INNER JOIN Trip ON PIT.trip_no=Trip.trip_no
) AS t3
GROUP BY t3.ID_psg
HAVING COUNT(*)=2
