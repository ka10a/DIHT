WITH t AS (SELECT ROW_NUMBER() OVER(ORDER BY PIT.date, Trip.time_out, PIT.ID_psg) no, Trip.trip_no, PIT.date, Trip.ID_comp
FROM Pass_in_trip AS PIT INNER JOIN Trip ON Trip.trip_no = PIT.trip_no
WHERE CONVERT(CHAR(7), PIT.date, 120) = '2003-04' AND Trip.town_from = 'Rostov') 

SELECT (SELECT name FROM Company WHERE ID_comp = t.ID_comp) AS name, trip_no, date
FROM t
WHERE no = 5
