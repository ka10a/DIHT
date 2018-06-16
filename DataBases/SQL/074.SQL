WITH t AS (SELECT 'Russia' AS Country, class FROM Classes WHERE country='Russia')

SELECT * FROM t
UNION
SELECT country, class FROM Classes
WHERE (SELECT COUNT(*) FROM t) = 0
