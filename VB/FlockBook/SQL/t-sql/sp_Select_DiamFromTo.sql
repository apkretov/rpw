USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelect_DiamFromTo" AND type = "P")
    DROP PROCEDURE spSelect_DiamFromTo
GO
CREATE PROCEDURE spSelect_DiamFromTo (@Diam char(2)) AS
    SELECT DiamFrom, DiamTo FROM Diameter
	WHERE Diam = @Diam
GO
spSelect_DiamFromTo "44"
GO