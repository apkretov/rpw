USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spInsert_Defects" AND type = "P")
    DROP PROCEDURE spInsert_Defects
GO
CREATE PROCEDURE spInsert_Defects (@Defect varchar(50), @Remark varchar(150)) AS
    INSERT INTO Defects (Defect, Remark)
	VALUES (@Defect, @Remark)
GO
SELECT * FROM Defects
GO
spInsert_Defects "KDFADSF", "ADSFASD"
GO
SELECT * FROM Defects
GO