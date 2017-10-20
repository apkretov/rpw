USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spCount_SheepGoat_IDDam" AND type = "P")
    DROP PROCEDURE spCount_SheepGoat_IDDam
GO
CREATE PROCEDURE spCount_SheepGoat_IDDam (@IDDam char(6)) AS
    SELECT COUNT(IDDam) AS CountIDDam
	FROM SheepGoat
	GROUP BY IDDam
	HAVING (IDDam = @IDDam)
GO 
spCount_SheepGoat_IDDam "¿¿0001"
GO