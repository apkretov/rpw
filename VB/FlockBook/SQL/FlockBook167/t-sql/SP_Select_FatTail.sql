USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelect_FatTail" AND TYPE = "P")
    DROP PROCEDURE spSelect_FatTail
GO
CREATE PROCEDURE spSelect_FatTail AS
    SELECT * FROM FatTail
	WHERE FatTail <> "-"
GO
spSelect_FatTail
GO