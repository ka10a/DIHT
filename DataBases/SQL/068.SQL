WITH t2 AS (SELECT ISNULL(t1.cnt, 0) + ISNULL(t11.cnt, 0) AS full_cnt, t1.town_from, t1.town_to
FROM (SELECT COUNT(*) AS cnt, town_from, town_to FROM Trip GROUP BY town_from, town_to) as t1
FULL JOIN (SELECT COUNT(*) AS cnt, town_from, town_to FROM Trip GROUP BY town_from, town_to) AS t11
ON t1.town_from=t11.town_to AND t1.town_to=t11.town_from)

SELECT COUNT(*)/2 FROM t2
WHERE full_cnt >= ALL(SELECT full_cnt FROM t2)
