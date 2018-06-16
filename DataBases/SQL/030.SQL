SELECT t.point, t.date, SUM(t.out) as out, SUM(t.inc) as inc
FROM
(SELECT inp.point, inp.date, SUM(inc) as inc, null as out
FROM Income as inp
GROUP BY inp.point, inp.date
UNION
SELECT out.point, out.date, NULL as inc, SUM(out) as out
FROM Outcome as out
GROUP BY out.point, out.date) as t
GROUP BY t.point, t.date