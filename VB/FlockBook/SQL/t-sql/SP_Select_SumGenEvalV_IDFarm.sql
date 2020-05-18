USE FlockBook
GO

IF EXISTS (SELECT name FROM sysobjects WHERE 
	NAME = "spSelect_SumGenEvalV_IDFarm" AND type = "P")
DROP PROCEDURE spSelect_SumGenEvalV_IDFarm
GO

CREATE PROCEDURE spSelect_SumGenEvalV_IDFarm (@IDFarm char(2))
AS
SELECT * FROM SumGenEvalV
WHERE IDFarm = @IDFarm
GO

spSelect_SumGenEvalV_IDFarm "¿¿"
GO