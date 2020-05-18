USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spDelete_StandGrease_IDBreed" AND type = 
    "P")
    DROP PROCEDURE spDelete_StandGrease_IDBreed
GO
CREATE PROCEDURE spDelete_StandGrease_IDBreed (@IDBreed char(2)) AS
    DELETE StandGrease
	WHERE IDBreed = @IDBreed
GO
SELECT * FROM StandGrease
GO
spDelete_StandGrease_IDBreed "99"
GO
SELECT * FROM StandGrease
GO