SELECT DISTINCT name
FROM Ships, Classes
WHERE type = 'bb' AND ships.launched >= 1922 AND displacement > 35000 AND ships.class = classes.class
