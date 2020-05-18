use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelect_WeightAnnual_IDSheepGoatDateAnnl" AND type = "P")
DROP PROCEDURE spSelect_WeightAnnual_IDSheepGoatDateAnnl
GO

CREATE PROCEDURE spSelect_WeightAnnual_IDSheepGoatDateAnnl_Prev0 (@IDSheepGoat char(6), 
	@DateAnnl varchar(8))
AS
SET DATEFORMAT dmy
select * from WeightAnnual
where IDSheepGoat = @IDSheepGoat and DateAnnl = CAST(@DateAnnl AS smalldatetime)
go

--spSelect_WeightAnnual_IDSheepGoatDateAnnl "¿¡0000", "01.01.01"
--go