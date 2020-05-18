USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelect_Farms_Dbc" AND type = "P")
    DROP PROCEDURE spSelect_Farms_Dbc
GO
CREATE PROCEDURE spSelect_Farms_Dbc AS
    SELECT IDFarm 
	FROM Farms
	WHERE IDFarm <> "-"
	ORDER BY IDFarm 
GO
spSelect_Farms_Dbc 
GO