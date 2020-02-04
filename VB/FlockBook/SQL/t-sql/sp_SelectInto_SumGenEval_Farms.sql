USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_SumGenEval_Farms" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_SumGenEval_Farms
GO
CREATE PROCEDURE spSelectInto_SumGenEval_Farms (@IDFarm char(2)) 
AS
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumGenEval_Farms" AND type = "U")
    DROP TABLE SumGenEval_Farms
SELECT Farms.IDFarm, Persons.Nam -- Create a new one.
    INTO SumGenEval_Farms 
    FROM Farms INNER JOIN Persons ON Farms.IDPersFarmer = Persons.IDPers
    WHERE Farms.IDFarm = @IDFarm
GO
spSelectInto_SumGenEval_Farms "¿¿"
GO
SELECT * FROM SumGenEval_Farms
GO