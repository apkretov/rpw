use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelect_Offspring_IDDamCycle_Kyes" AND type = "P")
DROP PROCEDURE spSelect_Offspring_IDDamCycle_Kyes
GO

CREATE PROCEDURE spSelect_Offspring_IDDamCycle_Kyes (@IDDam char(6), @Cycle tinyint)
AS
select IDDam, Cycle, NoLambKid from Offspring
where IDDam = @IDDam and Cycle = @Cycle
go

spSelect_Offspring_IDDamCycle_Kyes "¿¡0000", 1
go
