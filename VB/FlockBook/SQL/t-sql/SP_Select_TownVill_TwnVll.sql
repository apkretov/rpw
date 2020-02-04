USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_TownVill_TwnVll" AND type = "P")
    DROP PROCEDURE spSelect_TownVill_TwnVll
GO
CREATE PROCEDURE spSelect_TownVill_TwnVll (@TownVill varchar(50)) AS
    SELECT *
	FROM TownVill
	WHERE TownVill = @TownVill
GO
spSelect_TownVill_TwnVll "KDFADSF"
GO
