use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spDelete_Weight7Mon_IDLambKid" AND type = "P")
DROP PROCEDURE spDelete_Weight7Mon_IDLambKid
GO

CREATE PROCEDURE spDelete_Weight7Mon_IDLambKid (@IDLambKid char(6))
AS
delete Weight7Mon
where IDLambKid = @IDLambKid
go

--spDelete_Weight7Mon_IDLambKid "¿¡0000"
--go	