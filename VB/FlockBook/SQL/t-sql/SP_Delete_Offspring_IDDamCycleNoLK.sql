use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spDelete_Offspring_IDDamCycleNoLK" AND type = "P")
DROP PROCEDURE spDelete_Offspring_IDDamCycleNoLK
GO

CREATE PROCEDURE spDelete_Offspring_IDDamCycleNoLK (@IDDam char(6), @Cycle tinyint, 
	@NoLambKid tinyint)
AS
delete Offspring
where IDDam = @IDDam and Cycle = @Cycle and NoLambKid = @NoLambKid
go