USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spDelete_Breeds_IDBreed" AND type = "P")
    DROP PROCEDURE spDelete_Breeds_IDBreed
GO
CREATE PROCEDURE spDelete_Breeds_IDBreed (@IDBreed char(2)) AS
    DELETE Breeds
	WHERE IDBreed = @IDBreed
GO
SELECT * FROM Breeds
GO
spDelete_Breeds_IDBreed "99"
GO
SELECT * FROM Breeds
GO