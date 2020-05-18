USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spInsert_Busy" AND type = "P")
    DROP PROCEDURE spInsert_Busy
GO
CREATE PROCEDURE spInsert_Busy (@Busy bit) AS
    INSERT INTO Busy (Busy)
	VALUES (@Busy)
GO
SELECT * FROM Busy
GO
spInsert_Busy 0
GO
SELECT * FROM Busy
GO