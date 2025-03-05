use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spDelete_Mate_IDDamCycle" AND type = "P")
DROP PROCEDURE spDelete_Mate_IDDamCycle
GO

CREATE PROCEDURE spDelete_Mate_IDDamCycle (@IDDam char(6), @Cycle tinyint)
AS
delete Mate
where IDDam = @IDDam and Cycle = @Cycle
go