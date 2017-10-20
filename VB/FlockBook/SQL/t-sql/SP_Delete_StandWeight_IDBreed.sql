USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spDelete_StandWeight_IDBreed" AND type = 
    "P")
    DROP PROCEDURE spDelete_StandWeight_IDBreed
GO
CREATE PROCEDURE spDelete_StandWeight_IDBreed (@IDBreed char(2)) AS
    DELETE StandWeight
	WHERE IDBreed = @IDBreed
GO
SELECT * FROM StandWeight
GO
spDelete_StandWeight_IDBreed "99"
GO
SELECT * FROM StandWeight
GO