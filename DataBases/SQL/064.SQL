SELECT Inc.point, Inc.date, 'inc' as oper_type, SUM(Inc.inc) as money FROM Income as Inc
LEFT JOIN Outcome AS Out ON Inc.point=Out.point AND Inc.date=Out.date
WHERE Out.out IS NULL
GROUP BY Inc.point, Inc.date
UNION
SELECT Out.point, Out.date, 'out' as oper_type, SUM(Out.out) as money FROM Outcome AS Out
LEFT JOIN Income as Inc ON Inc.point=Out.point AND Inc.date=Out.date
WHERE Inc.inc IS NULL
GROUP BY Out.point, Out.date
