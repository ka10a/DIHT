SELECT DISTINCT Con.FirstName, Ad.City FROM
(Contact AS Con
INNER JOIN StoreContact AS SC on Con.ContactID = SC.ContactID
INNER JOIN Store As St ON SC.StoreID=St.StoreID
INNER JOIN Customer AS Cust ON St.CustomerID=Cust.CustomerID
INNER JOIN CustomerAddress AS CA ON Cust.CustomerID=CA.CustomerID
INNER JOIN Address AS Ad ON CA.AddressID=Ad.AddressID)
WHERE Cust.CustomerType='S'
ORDER BY Con.FirstName, Ad.City;