USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_Oblasts_Obl" AND type = "P")
    DROP PROCEDURE spSelect_Oblasts_Obl
GO
CREATE PROCEDURE spSelect_Oblasts_Obl (@Oblast varchar(50)) AS
    SELECT *
	FROM Oblasts
	WHERE Oblast = @Oblast
GO
spSelect_Oblasts_Obl "Баткенская"
GO
