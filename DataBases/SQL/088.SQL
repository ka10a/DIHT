WITH t AS (SELECT ID_psg, MIN(ID_comp) AS comp, COUNT(PIT.trip_no) AS cnt FROM Pass_in_trip AS PIT
INNER JOIN Trip ON Trip.trip_no=PIT.trip_no
GROUP BY ID_psg
HAVING COUNT(DISTINCT ID_comp) = 1)

SELECT (SELECT name FROM Passenger AS Pass WHERE Pass.ID_psg=t.ID_psg), cnt, (SELECT name FROM Company WHERE Company.ID_comp=comp) 
FROM t
WHERE cnt >= ALL (SELECT cnt FROM t)
