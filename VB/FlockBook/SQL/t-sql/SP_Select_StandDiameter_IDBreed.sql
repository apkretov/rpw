USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects 
    WHERE name = "spSelect_StandDiameter_IDBreed" AND type = "P")
    DROP PROCEDURE spSelect_StandDiameter_IDBreed
GO
CREATE PROCEDURE spSelect_StandDiameter_IDBreed (@IDBreed char(2)) AS
    SELECT * FROM StandDiameter
	WHERE IDBreed = @IDBreed
GO
spSelect_StandDiameter_IDBreed " »"
GO