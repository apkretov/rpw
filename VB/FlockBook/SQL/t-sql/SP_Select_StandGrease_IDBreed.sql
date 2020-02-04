USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelect_StandGrease_IDBreed" AND 
    type = "P")
    DROP PROCEDURE spSelect_StandGrease_IDBreed
GO
CREATE PROCEDURE spSelect_StandGrease_IDBreed (@IDBreed char(2)) AS
    SELECT * FROM StandGrease
	WHERE IDBreed = @IDBreed
GO
spSelect_StandGrease_IDBreed " »"
GO