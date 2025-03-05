USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_BrsShG_Rayons" AND type = "P")
    DROP PROCEDURE spSelect_BrsShG_Rayons
GO
CREATE PROCEDURE spSelect_BrsShG_Rayons (@IDOblast int) AS
    SELECT IDRayon, Rayon FROM Rayons
	WHERE IDOblast = @IDOblast
	ORDER BY Rayon
GO
spSelect_BrsShG_Rayons 1
GO