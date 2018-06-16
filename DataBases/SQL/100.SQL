WITH Out1 AS (SELECT date, point, (SELECT COUNT(*) FROM Outcome WHERE Outcome.date=Out.date and Outcome.code <= Out.code) AS N, out
FROM Outcome AS Out)

SELECT ISNULL(Inc1.date, Out1.date) AS date, ISNULL(Inc1.N, Out1.N) AS N, Inc1.point, Inc1.inc, Out1.point, Out1.out
FROM
(SELECT date, point, (SELECT COUNT(*) FROM Income WHERE Income.date = Inc.date and Income.code <= Inc.code) AS N, inc
FROM Income AS Inc) AS Inc1
FULL JOIN
Out1 ON Inc1.date=Out1.date AND Inc1.N=Out1.N
