SELECT COUNT(*) OVER (ORDER BY t.cnt DESC, t.maker, t.model) as number,
t.maker, t.model
FROM
(SELECT COUNT(*) OVER (PARTITION BY maker) cnt, maker, model FROM Product) t
