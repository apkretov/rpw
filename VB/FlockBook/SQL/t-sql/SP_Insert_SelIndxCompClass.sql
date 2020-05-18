USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spInsert_SelIndxCompClass" AND type = "P")
    DROP PROCEDURE spInsert_SelIndxCompClass
GO
CREATE PROCEDURE spInsert_SelIndxCompClass (@IDSheepGoat char(6), @SelIndx real, 
    @IDCompClass char(1)) AS
    INSERT INTO SelIndxCompClass (IDSheepGoat, SelIndx, IDCompClass)
        VALUES (@IDSheepGoat, @SelIndx / 10, @IDCompClass)
GO
spInsert_SelIndxCompClass "¿¡0001", 39, "2"
GO