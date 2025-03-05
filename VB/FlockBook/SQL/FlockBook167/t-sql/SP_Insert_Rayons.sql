USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spInsert_Rayons" AND type = "P")
    DROP PROCEDURE spInsert_Rayons
GO
CREATE PROCEDURE spInsert_Rayons (@IDOblast int, @Rayon varchar(50), @Remark varchar(150)) AS
    INSERT INTO Rayons (IDOblast, Rayon, Remark)
	VALUES (@IDOblast, @Rayon, @Remark)
GO
SELECT * FROM Rayons
GO
spInsert_Rayons 1, "KDFADSF", "ADSFASD"
GO
SELECT * FROM Rayons
GO