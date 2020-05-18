use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spDelete_WeightWean_IDLambKid" AND type = "P")
DROP PROCEDURE spDelete_WeightWean_IDLambKid
GO

CREATE PROCEDURE spDelete_WeightWean_IDLambKid (@IDLambKid char(6))
AS
delete WeightWean
where IDLambKid = @IDLambKid
go

spDelete_WeightWean_IDLambKid "¿¡0000"
go