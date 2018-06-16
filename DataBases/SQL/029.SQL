SELECT inp.point, inp.date, inc, out
FROM Income_o as inp
LEFT JOIN Outcome_o as out
ON inp.point = out.point AND inp.date = out.date
UNION
SELECT out.point, out.date, inc, out
FROM Income_o as inp
RIGHT JOIN Outcome_o as out
ON inp.point = out.point AND inp.date = out.date