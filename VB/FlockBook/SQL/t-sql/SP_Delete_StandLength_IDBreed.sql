USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spDelete_StandLength_IDBreed" AND type = 
    "P")
    DROP PROCEDURE spDelete_StandLength_IDBreed
GO
CREATE PROCEDURE spDelete_StandLength_IDBreed (@IDBreed char(2)) AS
    DELETE StandLength
	WHERE IDBreed = @IDBreed
GO
SELECT * FROM StandLength
GO
spDelete_StandLength_IDBreed "99"
GO
SELECT * FROM StandLength
GO