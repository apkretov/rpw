USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spDelete_SheepGoat_IDShG" AND type = "P")
    DROP PROCEDURE spDelete_SheepGoat_IDShG
GO
CREATE PROCEDURE spDelete_SheepGoat_IDShG (@IDSheepGoatOrigin char(6)) AS
    DELETE SheepGoat
	WHERE IDSheepGoat = @IDSheepGoatOrigin
GO
spDelete_SheepGoat_IDShG "adkdf"
GO