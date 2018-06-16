WITH t AS(SELECT ROW_NUMBER() OVER(ORDER BY code) AS no, code, price
FROM PC)

SELECT code, (SELECT AVG(price) FROM t AS t1 WHERE t1.no >= t.no AND t1.no <= t.no + 5)  FROM t
WHERE t.no + 5 <= (SELECT COUNT(*) FROM t)