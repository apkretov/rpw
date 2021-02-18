USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_RptFarm" AND type = "P")
    DROP PROCEDURE spSelectInto_RptFarm
GO
CREATE PROCEDURE spSelectInto_RptFarm (@IDFarm char(2)) AS
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "RptFarm" AND type = "U")
    	DROP TABLE RptFarm -- Drop the previous table.
    SELECT Farms.IDFarm, Persons.Nam -- Create a new one.
	INTO RptFarm
    	FROM Farms INNER JOIN Persons ON Farms.IDPersFarmer = Persons.IDPers
    	WHERE Farms.IDFarm = @IDFarm
GO
spSelectInto_RptFarm "¿¿"
GO
SELECT * FROM RptFarm
GO