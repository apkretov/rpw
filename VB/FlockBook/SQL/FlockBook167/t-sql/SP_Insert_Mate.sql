USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spInsert_Mate" AND type = "P")
    DROP PROCEDURE spInsert_Mate
GO
CREATE PROCEDURE spInsert_Mate (@IDDam char(6), @Cycle tinyint, @CycleLambKid tinyint, 
    @DateMatFrom varchar(8), @IDSire char(6)) AS
    SET DATEFORMAT dmy
    INSERT INTO Mate(IDDam, Cycle, CycleLambKid, DateMatFrom, IDSire)
	VALUES (@IDDam, @Cycle, @CycleLambKid, CAST(@DateMatFrom AS smalldatetime), @IDSire)
GO
spInsert_Mate "¿¿0001", 5, 5, "01.01.01", "¿¿0000"
GO
SELECT * FROM Mate 
    WHERE IDDam = "¿¿0001"
GO