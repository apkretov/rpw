use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelect_Offspring_IDDamCycleNoLK" AND type = "P")
DROP PROCEDURE spSelect_Offspring_IDDamCycleNoLK
GO

CREATE PROCEDURE spSelect_Offspring_IDDamCycleNoLK (@IDDam char(6), @Cycle tinyint, 
	@NoLambKid tinyint)
AS
select * from Offspring
where IDDam = @IDDam and Cycle = @Cycle and NoLambKid = @NoLambKid
go

spSelect_Offspring_IDDamCycleNoLK "¿¡0000", 1, 1
go