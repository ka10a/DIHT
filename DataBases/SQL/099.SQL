WITH Temp AS (SELECT ISNULL(Inc.point, Out.point) AS point, ISNULL(Inc.date, Out.date) AS date, Inc.inc, Out.out
FROM Income_o AS Inc
FULL JOIN Outcome_o AS Out ON Inc.date = Out.date AND Inc.point = Out.point)

SELECT T.point, T.date AS DP, 
CASE
WHEN T.out IS NULL THEN T.date
ELSE (
SELECT MIN(Day) as Min_Date
FROM (
SELECT DATEADD(dd, 1, T.date) AS Day
UNION ALL
SELECT DATEADD(dd, 2, T.date)
UNION ALL
SELECT DATEADD(dd, 3, T.date)
UNION ALL
SELECT DATEADD(dd, 1, (SELECT MIN(Temp.date) FROM Temp
WHERE date > T.date AND DATEADD(dd, 1, Temp.date) NOT IN (SELECT date FROM Outcome_o WHERE point = T.point) AND DATENAME(weekday, DATEADD(dd, 1, date)) <> 'Sunday')) ) AS dat
WHERE dat.Day NOT IN (SELECT date FROM Outcome_o WHERE point = T.point) AND DATENAME(weekday, Day) <> 'Sunday'
)
END AS DI
FROM Temp AS T
WHERE T.inc IS NOT NULL
