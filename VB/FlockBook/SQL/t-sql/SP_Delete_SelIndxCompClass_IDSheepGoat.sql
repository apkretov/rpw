USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects 
    WHERE name = "spDelete_SelIndxCompClass_IDSheepGoat" AND type = "P")
    DROP PROCEDURE spDelete_SelIndxCompClass_IDSheepGoat
GO
CREATE PROCEDURE spDelete_SelIndxCompClass_IDSheepGoat @IDSheepGoat char(6) AS
    DELETE SelIndxCompClass
	WHERE IDSheepGoat = @IDSheepGoat
GO
spDelete_SelIndxCompClass_IDSheepGoat "¿¡0000"
GO
SELECT * FROM SelIndxCompClass
G0