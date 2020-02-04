use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelect_WeightWean_IDLambKid" AND type = "P")
DROP PROCEDURE spSelect_WeightWean_IDLambKid
GO

CREATE PROCEDURE spSelect_WeightWean_IDLambKid (@IDLambKid char(6))
AS
select * from WeightWean
where IDLambKid = @IDLambKid
go

spSelect_WeightWean_IDLambKid "¿¡0000"
go