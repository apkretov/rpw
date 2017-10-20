USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects 
    WHERE name = "spUpdate_SelIndxCompClass_IDSheepGoat" AND type = "P")
    DROP PROCEDURE spUpdate_SelIndxCompClass_IDSheepGoat
GO
CREATE PROCEDURE spUpdate_SelIndxCompClass_IDSheepGoat (@IDSheepGoat char(6), @SelIndx real, 
    @IDCompClass char(1)) AS
    SET DATEFORMAT dmy
    UPDATE SelIndxCompClass
	SET SelIndx = @SelIndx / 10, IDCompClass = @IDCompClass
	    WHERE IDSheepGoat = @IDSheepGoat
GO
spUpdate_SelIndxCompClass_IDSheepGoat "¿¡0000", 42, 3
GO
SELECT * FROM SelIndxCompClass
GO