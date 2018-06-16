SELECT Ships.name, Ships.launched,
CASE
WHEN Ships.launched > (SELECT MAX(date) AS date FROM Battles)
THEN NULL
WHEN Ships.launched IS NULL
THEN (SELECT MAX(name) FROM Battles WHERE date=(SELECT MAX(date) AS date FROM Battles))
ELSE (
SELECT MAX(name) FROM Battles WHERE date=(SELECT MIN(date) FROM Battles WHERE DATEPART(yyyy, date) >= Ships.launched)
)
END
FROM Ships
