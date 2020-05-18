USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_SheepGoat_Grid" AND type = "P")
    DROP PROCEDURE spSelect_SheepGoat_Grid
GO
CREATE PROCEDURE spSelect_SheepGoat_Grid (@IDFarm char(2)) AS
    SELECT IDSheepGoat AS [Находящиеся на ферме]
	FROM SheepGoat
	WHERE (IDFarm = @IDFarm)
GO
spSelect_SheepGoat_Grid "АА"
GO
