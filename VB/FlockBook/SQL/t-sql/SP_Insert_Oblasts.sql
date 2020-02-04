USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spInsert_Oblasts" AND type = "P")
    DROP PROCEDURE spInsert_Oblasts
GO
CREATE PROCEDURE spInsert_Oblasts (@IDCountry int, @Oblast varchar(50), @Remark varchar(150)) AS
    INSERT INTO Oblasts (IDCountry, Oblast, Remark)
	VALUES (@IDCountry, @Oblast, @Remark)
GO
SELECT * FROM Oblasts
GO
spInsert_Oblasts 11, "KDFADSF", "ADSFASD"
GO
SELECT * FROM Oblasts
GO