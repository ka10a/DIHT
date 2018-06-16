SELECT 
(SELECT MIN(trip_no) FROM Trip) AS tr1,
(SELECT MIN(trip_no) FROM Trip WHERE trip_no > (SELECT MIN(trip_no) FROM Trip)) AS tr2,
(SELECT MIN(trip_no) FROM Trip WHERE trip_no > (SELECT MIN(trip_no) FROM Trip WHERE trip_no > (SELECT MIN(trip_no) FROM TRIP))) AS tr3,
(SELECT MAX(trip_no) FROM Trip WHERE trip_no < (SELECT MAX(trip_no) FROM Trip WHERE trip_no < (SELECT MAX(trip_no) FROM TRIP))) AS tr4,
(SELECT MAX(trip_no) FROM Trip WHERE trip_no < (SELECT MAX(trip_no) FROM Trip)) AS tr5,
(SELECT MAX(trip_no) FROM Trip) AS tr6
