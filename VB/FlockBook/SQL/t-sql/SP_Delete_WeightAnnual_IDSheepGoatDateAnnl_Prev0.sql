use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spDelete_WeightAnnual_IDSheepGoatDateAnnl" AND type = "P")
DROP PROCEDURE spDelete_WeightAnnual_IDSheepGoatDateAnnl
GO

CREATE PROCEDURE spDelete_WeightAnnual_IDSheepGoatDateAnnl_Prev0 (@IDSheepGoat char(6), 
	@DateAnnl varchar(8))
AS
SET DATEFORMAT dmy
delete WeightAnnual
where IDSheepGoat = @IDSheepGoat and DateAnnl = CAST(@DateAnnl AS smalldatetime)
go

--spDelete_WeightAnnual_IDSheepGoatDateAnnl "¿¡0000", "31.12.99"
--go