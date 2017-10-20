USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spDelete_StandDiameter_IDBreed" AND type = 
    "P")
    DROP PROCEDURE spDelete_StandDiameter_IDBreed
GO
CREATE PROCEDURE spDelete_StandDiameter_IDBreed (@IDBreed char(2)) AS
    DELETE StandDiameter
	WHERE IDBreed = @IDBreed
GO
SELECT * FROM StandDiameter
GO
spDelete_StandDiameter_IDBreed "99"
GO
SELECT * FROM StandDiameter
GO