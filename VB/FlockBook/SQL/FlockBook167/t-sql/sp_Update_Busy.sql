USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spUpdate_Busy" AND type = "P")
    DROP PROCEDURE spUpdate_Busy
GO
CREATE PROCEDURE spUpdate_Busy (@Busy bit) AS
    UPDATE Busy
	SET Busy = @Busy
GO
SELECT * FROM Busy
GO
spUpdate_Busy 0
GO
SELECT * FROM Busy
GO