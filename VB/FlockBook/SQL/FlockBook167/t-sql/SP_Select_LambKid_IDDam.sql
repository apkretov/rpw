use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelect_LambKid_IDDam" AND type = "P")
DROP PROCEDURE spSelect_LambKid_IDDam
GO

CREATE PROCEDURE spSelect_LambKid_IDDam (@IDDam char(6))
AS
select * from LambKid
where IDDam = @IDDam
go

spSelect_LambKid_IDDam "¿¡0000"
go