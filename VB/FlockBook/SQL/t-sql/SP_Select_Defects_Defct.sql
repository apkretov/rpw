USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_Defects_Defct" AND type = "P")
    DROP PROCEDURE spSelect_Defects_Defct
GO
CREATE PROCEDURE spSelect_Defects_Defct (@Defect varchar(50)) AS
    SELECT *
	FROM Defects
	WHERE Defect = @Defect
GO
spSelect_Defects_Defct "Отсутсвие рога"
GO
