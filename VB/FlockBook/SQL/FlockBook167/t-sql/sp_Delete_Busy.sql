USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spDelete_Busy" AND type = "P")
    DROP PROCEDURE spDelete_Busy
GO
CREATE PROCEDURE spDelete_Busy AS
    DELETE Busy
GO
SELECT * FROM Busy
GO
spDelete_Busy
GO
SELECT * FROM Busy
GO