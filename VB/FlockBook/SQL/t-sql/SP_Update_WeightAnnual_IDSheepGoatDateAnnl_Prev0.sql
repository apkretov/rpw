use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spUpdate_WeightAnnual_IDSheepGoatDateAnnl" AND type = "P")
DROP PROCEDURE spUpdate_WeightAnnual_IDSheepGoatDateAnnl
GO

CREATE PROCEDURE spUpdate_WeightAnnual_IDSheepGoatDateAnnl_Prev0 (@IDSheepGoat char(6), 
	@DateAnnlOrigin varchar(8), @DateAnnl varchar(8), @WtAnnl real, @Age1Yr bit)
AS
SET DATEFORMAT dmy
update WeightAnnual
set DateAnnl = CAST(@DateAnnl AS smalldatetime), WtAnnl = @WtAnnl, Age1Yr = @Age1Yr
where IDSheepGoat = @IDSheepGoat and DateAnnl = CAST(@DateAnnlOrigin AS smalldatetime)
go

--spUpdate_WeightAnnual_IDSheepGoatDateAnnl "¿¡0000", "01.01.01", "31.12.99", 60, 0
--go