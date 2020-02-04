USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_BrsDivsn_Countr" AND type = "P")
    DROP PROCEDURE spSelect_BrsDivsn_Countr
GO
CREATE PROCEDURE spSelect_BrsDivsn_Countr AS
    SELECT Country AS Страна, Remark AS Заметки
	FROM Countries
	WHERE (Country <> "-")
	ORDER BY Country
GO
spSelect_BrsDivsn_Countr 
GO