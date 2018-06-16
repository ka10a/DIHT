SELECT CR.Name, MAX(Con.FirstName) ContactFirstName
FROM (CountryRegion AS CR
	JOIN Address AS Ad ON CR.CountryRegionCode = Ad.CountryRegionCode
	JOIN CustomerAddress AS CA ON Ad.AddressID = CA.AddressID
	JOIN Customer AS Cust ON CA.CustomerID = Cust.CustomerID
	JOIN SalesOrderHeader AS SOH ON SOH.CustomerID = Cust.CustomerID
	JOIN Contact AS Con ON Con.ContactID = SOH.ContactID)
GROUP BY CR.Name, Con.FirstName
HAVING COUNT(*) >= ALL (
SELECT COUNT(*)
FROM (CountryRegion AS CR1
	JOIN Address AS Ad1 ON CR1.CountryRegionCode = Ad1.CountryRegionCode
	JOIN CustomerAddress AS CA1 ON Ad1.AddressID = CA1.AddressID
	JOIN Customer AS Cust1 ON CA1.CustomerID = Cust1.CustomerID
	JOIN SalesOrderHeader AS SOH1 ON SOH1.CustomerID = Cust1.CustomerID
	JOIN Contact AS Con1 ON Con1.ContactID = SOH1.ContactID)
WHERE CR1.Name=CR.Name
GROUP BY CR1.Name, Con1.FirstName)