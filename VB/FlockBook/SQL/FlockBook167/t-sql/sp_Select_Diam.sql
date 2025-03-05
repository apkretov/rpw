USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelect_Diam" AND type = "P")
    DROP PROCEDURE spSelect_Diam
GO
CREATE PROCEDURE spSelect_Diam AS
    SELECT * FROM Diameter
	WHERE Diam <> "-"
GO
spSelect_Diam
GO