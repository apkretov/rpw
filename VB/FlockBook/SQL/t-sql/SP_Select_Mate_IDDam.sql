USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelect_Mate_IDDam" AND type = "P")
    DROP PROCEDURE spSelect_Mate_IDDam
GO
CREATE PROCEDURE spSelect_Mate_IDDam (@IDDam char(6)) AS
    SELECT * FROM Mate
	WHERE IDDam = @IDDam
GO
spSelect_Mate_IDDam "¿¿0001"
GO