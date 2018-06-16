SELECT Classes.class, ISNULL(MIN(launched), NULL) FROM Classes
LEFT JOIN Ships ON Ships.class=Classes.class
GROUP BY Classes.class
