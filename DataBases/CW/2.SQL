SELECT Cust.CustomerID FROM Customer as Cust
EXCEPT
SELECT CustomerID FROM SalesOrderHeader as SOH
WHERE OrderDate BETWEEN '2004-01-01' AND GETDATE();