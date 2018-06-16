SELECT Ind.FirstName, Ind.MiddleName, Ind.LastName, Ad.Phone FROM
(Individual AS Ind JOIN CustomerAddress AS CustAdd ON Ind.CustomerID=CustAdd.CustomerID)
JOIN Address AS Ad ON  CustAdd.AddressID=Ad.AddressID
WHERE Ad.Phone LIKE '1 (11) 500 555-01%';