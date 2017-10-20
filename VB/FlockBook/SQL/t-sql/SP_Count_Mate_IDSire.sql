USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spCount_Mate_IDSire" AND type = "P")
    DROP PROCEDURE spCount_Mate_IDSire
GO
CREATE PROCEDURE spCount_Mate_IDSire (@IDSire char(6)) AS
    SELECT COUNT(IDSire) AS CountIDSire
	FROM Mate
	GROUP BY IDSire
	HAVING (IDSire = @IDSire)
GO 
spCount_Mate_IDSire "¿¿0000"
GO