USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spDelete_Oblasts_IDObl" AND type = "P")
    DROP PROCEDURE spDelete_Oblasts_IDObl
GO
CREATE PROCEDURE spDelete_Oblasts_IDObl (@IDOblast int) AS
    DELETE Oblasts
	WHERE IDOblast = @IDOblast
GO
spDelete_Oblasts_IDObl 8
GO
