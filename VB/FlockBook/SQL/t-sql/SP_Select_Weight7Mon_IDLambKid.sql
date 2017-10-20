use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelect_Weight7Mon_IDLambKid" AND type = "P")
DROP PROCEDURE spSelect_Weight7Mon_IDLambKid
GO

CREATE PROCEDURE spSelect_Weight7Mon_IDLambKid (@IDLambKid char(6))
AS
SET DATEFORMAT dmy
select * from Weight7Mon
where IDLambKid = @IDLambKid
go

spSelect_Weight7Mon_IDLambKid "¿¡0000"
go