USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spDelete_StandFatTail_IDBreed" AND type = 
    "P")
    DROP PROCEDURE spDelete_StandFatTail_IDBreed
GO
CREATE PROCEDURE spDelete_StandFatTail_IDBreed (@IDBreed char(2)) AS
    DELETE StandFatTail
	WHERE IDBreed = @IDBreed
GO
SELECT * FROM StandFatTail
GO
spDelete_StandFatTail_IDBreed "99"
GO
SELECT * FROM StandFatTail
GO