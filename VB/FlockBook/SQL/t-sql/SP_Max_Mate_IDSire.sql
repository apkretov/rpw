USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spMax_Mate_IDSire" AND type = "P")
    DROP PROCEDURE spMax_Mate_IDSire
GO
CREATE PROCEDURE spMax_Mate_IDSire (@IDSire char(6)) AS
    SELECT IDSire, MAX(DateMatFrom) AS MaxDateMatFrom
	FROM Mate
	GROUP BY IDSire
	HAVING (IDSire = @IDSire)
GO 
spMax_Mate_IDSire "¿¿0000"
GO