WITH t AS (SELECT ID_psg, town_from
FROM Pass_in_trip AS PIT
INNER JOIN Trip AS Tr ON PIT.trip_no=Tr.trip_no
WHERE date <= ALL (SELECT date  FROM Pass_in_trip WHERE Pass_in_trip.ID_psg=PIT.ID_Psg) 
AND time_out <= ALL (SELECT time_out FROM Pass_in_trip
INNER JOIN Trip ON Pass_in_trip.trip_no=Trip.trip_no WHERE Pass_in_trip.ID_psg=PIT.ID_psg AND Pass_in_trip.date=PIT.date))

SELECT (SELECT name FROM Passenger AS Pass WHERE Pass.ID_psg=PIT.ID_psg), COUNT(*)
FROM Pass_in_trip AS PIT
INNER JOIN Trip ON PIT.trip_no=Trip.trip_no
WHERE 'Moscow' NOT IN (SELECT town_from FROM t AS t1 WHERE PIT.ID_psg=t1.ID_psg)
AND town_to='Moscow'
GROUP BY ID_psg
HAVING COUNT(*) > 1
