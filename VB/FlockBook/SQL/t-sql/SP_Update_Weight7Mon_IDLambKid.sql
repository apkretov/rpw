use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spUpdate_Weight7Mon_IDLambKid" AND type = "P")
DROP PROCEDURE spUpdate_Weight7Mon_IDLambKid
GO

CREATE PROCEDURE spUpdate_Weight7Mon_IDLambKid (@IDLambKid char(6), @Date7Mon varchar(8), 
	@Wt7Mon real)
AS
SET DATEFORMAT dmy
update Weight7Mon
set Date7Mon = CAST(@Date7Mon AS smalldatetime), Wt7Mon = @Wt7Mon/10
where IDLambKid = @IDLambKid
go

--spUpdate_Weight7Mon_IDLambKid "¿¡0000", "02.02.02", 50
--go