SELECT CustomerType, COUNT(CustomerID) as Cnt FROM Customer
GROUP BY CustomerType; 