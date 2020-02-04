use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelect_Mate_IDDamCycle" AND type = "P")
DROP PROCEDURE spSelect_Mate_IDDamCycle
GO

CREATE PROCEDURE spSelect_Mate_IDDamCycle (@IDDam char(6), @Cycle tinyint)
AS
select * from Mate
where IDDam = @IDDam and Cycle = @Cycle
go