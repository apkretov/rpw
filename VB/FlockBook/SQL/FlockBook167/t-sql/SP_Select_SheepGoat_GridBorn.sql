USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_SheepGoat_GridBorn" AND type = "P")
    DROP PROCEDURE spSelect_SheepGoat_GridBorn
GO
CREATE PROCEDURE spSelect_SheepGoat_GridBorn (@IDFarmBirth char(2)) AS
    SELECT IDSheepGoat AS [Рождённые на ферме]
	FROM SheepGoat
	WHERE (IDFarmBirth = @IDFarmBirth)
GO
spSelect_SheepGoat_GridBorn "АА"
GO
