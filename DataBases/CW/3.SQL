SELECT COUNT(Cust.CustomerID) FROM Customer as Cust
JOIN CustomerAddress as CA
ON Cust.CustomerID=CA.CustomerID
GROUP BY Cust.CustomerID
HAVING COUNT(AddressID) > 1;