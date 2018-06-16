WITH t AS (SELECT maker, COUNT(*) AS cnt FROM Product
GROUP BY maker)

SELECT maker, cnt FROM t
WHERE cnt >= ALL(SELECT cnt FROM t) OR cnt <= ALL (SELECT cnt FROM t)