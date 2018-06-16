WITH t1 AS (SELECT point, date, SUM(inc-out) AS remain
FROM (
SELECT point, date, SUM(ISNULL(inc, 0)) AS inc, 0 AS out
FROM Income GROUP BY point, date
UNION
SELECT point, date, 0, SUM(ISNULL(out, 0))
FROM Outcome GROUP BY point, date
) AS t2
GROUP BY point, date)

SELECT point, CONVERT(CHAR(10), date, 103), (SELECT SUM(remain) FROM t1 WHERE date <= t3.date AND point = t3.point) AS rem
FROM t1 AS t3