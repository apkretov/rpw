USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelect_Defects" AND type = "P")
    DROP PROCEDURE spSelect_Defects
GO
CREATE PROCEDURE spSelect_Defects AS
    SELECT * FROM Defects
	WHERE Defect <> "-"
GO
spSelect_Defects
GO