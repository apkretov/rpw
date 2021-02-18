USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spCount_SheepGoat_IDSire" AND type = "P")
    DROP PROCEDURE spCount_SheepGoat_IDSire
GO
CREATE PROCEDURE spCount_SheepGoat_IDSire (@IDSire char(6)) AS
    SELECT COUNT(IDSire) AS CountIDSire
	FROM SheepGoat
	GROUP BY IDSire
	HAVING (IDSire = @IDSire)
GO 
spCount_SheepGoat_IDSire "¿¿0000"
GO