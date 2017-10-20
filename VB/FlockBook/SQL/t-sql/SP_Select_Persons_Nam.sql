USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_Persons_Nam" AND type = "P")
    DROP PROCEDURE spSelect_Persons_Nam
GO
CREATE PROCEDURE spSelect_Persons_Nam (@Nam varchar(100)) AS
    SELECT *
	FROM Persons
	WHERE Nam = @Nam
GO
spSelect_Persons_Nam "KD, FAD, SF"
GO
