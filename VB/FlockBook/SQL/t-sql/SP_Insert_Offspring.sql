USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spInsert_Offspring" AND type = "P")
    DROP PROCEDURE spInsert_Offspring
GO
CREATE PROCEDURE spInsert_Offspring (@IDDam char(6), @Cycle tinyint, @NoLambKid tinyint, 
    @IDLambKid char(6), @IDSex char(1), @WtBirth real, @IDLiv char(1)) AS
    IF @WtBirth = 0 -- Convert zero to NULL.
	SET @WtBirth = NULL
    INSERT INTO Offspring(IDDam, Cycle, NoLambKid, IDLambKid, IDSex, WtBirth, IDLiv)
	VALUES (@IDDam, @Cycle, @NoLambKid, @IDLambKid, @IDSex, @WtBirth / 10, @IDLiv)
GO
SELECT * FROM Offspring WHERE IDDam = "юб0001"
GO
spInsert_Offspring "юб0001", 1, 4, "-", "-", 55, "2"
GO
SELECT * FROM Offspring WHERE IDDam = "юб0001"
GO