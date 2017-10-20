USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects 
    WHERE name = "spSelect_SelIndxCompClass_IDSheepGoat" AND type = "P")
    DROP PROCEDURE spSelect_SelIndxCompClass_IDSheepGoat
GO
CREATE PROCEDURE spSelect_SelIndxCompClass_IDSheepGoat (@IDSheepGoat char(6)) AS
    SELECT * FROM SelIndxCompClass
	WHERE IDSheepGoat = @IDSheepGoat
GO
spSelect_SelIndxCompClass_IDSheepGoat "¿¿0000"
GO