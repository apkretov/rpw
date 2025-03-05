USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spMin_Mate_IDSire" AND type = "P")
    DROP PROCEDURE spMin_Mate_IDSire
GO
CREATE PROCEDURE spMin_Mate_IDSire (@IDSire char(6)) AS
    SELECT IDSire, MIN(DateMatFrom) AS MinDateMatFrom
	FROM Mate
	GROUP BY IDSire
	HAVING (IDSire = @IDSire)
GO 
spMin_Mate_IDSire "¿¿0000"
GO