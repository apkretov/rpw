USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_Farms_GridTwnVll" AND type = "P")
    DROP PROCEDURE spSelect_Farms_GridTwnVll
GO
CREATE PROCEDURE spSelect_Farms_GridTwnVll (@TownVill varchar(50)) AS
    SELECT /*TownVill.TownVill AS [Населённый пункт],*/ Farms.IDFarm AS Ферма/*Фермы*/
	FROM TownVill 
	    INNER JOIN Farms ON 
		TownVill.IDTownVill = Farms.IDTownVill
	WHERE TownVill.TownVill = @TownVill
	ORDER BY Farms.IDFarm
GO
spSelect_Farms_GridTwnVll "БАТК01"
GO


