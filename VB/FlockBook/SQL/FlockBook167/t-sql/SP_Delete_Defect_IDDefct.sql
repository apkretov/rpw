USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spDelete_Defects_IDDefct" AND type = "P")
    DROP PROCEDURE spDelete_Defects_IDDefct
GO
CREATE PROCEDURE spDelete_Defects_IDDefct (@IDDefect int) AS
    DELETE Defects
	WHERE IDDefect = @IDDefect
GO
SELECT * FROM Defects
GO
spDelete_Defects_IDDefct 4
GO
SELECT * FROM Defects
GO