use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spDelete_LambKid_IDDamCycle" AND type = "P")
DROP PROCEDURE spDelete_LambKid_IDDamCycle
GO

CREATE PROCEDURE spDelete_LambKid_IDDamCycle (@IDDam char(6), @Cycle tinyint)
AS
delete LambKid
where IDDam = @IDDam and Cycle = @Cycle
go