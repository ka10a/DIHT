WITH t AS (SELECT ID_psg, COUNT(Trip.trip_no) AS trip_cnt
FROM Trip INNER JOIN Pass_in_trip AS PIT ON Trip.trip_no = PIT.trip_no
GROUP BY ID_psg
HAVING COUNT(DISTINCT ID_comp) = 1)

SELECT (SELECT name FROM Passenger AS P WHERE t.ID_psg = P.ID_psg) AS name, MIN(trip_cnt) AS CNT
FROM t
GROUP BY ID_psg
HAVING MIN(trip_cnt) >= ALL (SELECT trip_cnt FROM t)
