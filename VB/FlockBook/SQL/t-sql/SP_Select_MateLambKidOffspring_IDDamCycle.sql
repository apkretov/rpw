use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelect_MateLambKidOffspring_IDDamCycle" AND type = "P")
DROP PROCEDURE spSelect_MateLambKidOffspring_IDDamCycle
GO

CREATE PROCEDURE spSelect_MateLambKidOffspring_IDDamCycle (@IDDam char(6))
AS
SET DATEFORMAT dmy
select * from MateLambKidOffspring
where IDDam = @IDDam
go

spSelect_MateLambKidOffspring_IDDamCycle "¿¡0000"
go