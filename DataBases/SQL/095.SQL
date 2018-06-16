SELECT
(SELECT name FROM Company WHERE ID_comp=Trip.ID_comp) AS company_name,
(SELECT Y.CCC
FROM (SELECT SUM(R.CNT) AS CCC, R.ID_comp
FROM (SELECT COUNT(DISTINCT PIT.trip_no) AS CNT, TR.ID_comp, (SELECT name FROM Company AS A1 WHERE A1.ID_comp = TR.ID_comp) AS company_name, PIT.date
FROM Pass_in_trip AS PIT INNER JOIN Trip AS TR ON PIT.trip_no = TR.trip_no INNER JOIN Company AS CCC ON CCC.ID_comp = TR.ID_comp
GROUP BY TR.ID_comp, PIT.date) AS R
GROUP BY R.ID_comp) AS Y
WHERE Y.ID_comp = Trip.ID_comp) AS flights,
COUNT(DISTINCT plane) AS planes,
COUNT(DISTINCT ID_psg) AS diff_psngrs,
COUNT(ID_psg) AS total_psngrs
FROM Pass_in_trip  AS PIT
INNER JOIN Trip ON Trip.trip_no=PIT.trip_no
GROUP BY ID_comp
