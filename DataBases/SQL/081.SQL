SELECT code, point, date, out
FROM (
SELECT CONVERT(CHAR(7), Out.date, 120
) AS month
FROM Outcome AS Out
GROUP BY CONVERT(CHAR(7), Out.date, 120)
HAVING
(SELECT SUM(out) FROM Outcome WHERE CONVERT(CHAR(7), Out.date, 120) = CONVERT(CHAR(7), date, 120)) >= 
ALL (SELECT SUM(out) FROM Outcome GROUP BY CONVERT(CHAR(7), date, 120))) AS t INNER JOIN Outcome ON t.month = CONVERT(CHAR(7), date, 120)
