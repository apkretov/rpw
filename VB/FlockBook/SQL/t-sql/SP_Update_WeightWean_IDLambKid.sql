use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spUpdate_WeightWean_IDLambKid" AND type = "P")
DROP PROCEDURE spUpdate_WeightWean_IDLambKid
GO

CREATE PROCEDURE spUpdate_WeightWean_IDLambKid (@IDLambKid char(6), @DateWean varchar(8), 
	@WtWean real)
AS
SET DATEFORMAT dmy
update WeightWean
set DateWean = CAST(@DateWean AS smalldatetime), WtWean = @WtWean/10
where IDLambKid = @IDLambKid
go

spUpdate_WeightWean_IDLambKid "¿¡0000", "02.02.02", 111
go