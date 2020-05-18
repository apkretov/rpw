use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spDelete_WoolAnnual_IDSheepGoatDateShearAnnl" AND type = "P")
DROP PROCEDURE spDelete_WoolAnnual_IDSheepGoatDateShearAnnl
GO

CREATE PROCEDURE spDelete_WoolAnnual_IDSheepGoatDateShearAnnl_Prev0 (@IDSheepGoat char(6), 
	@DateShearAnnl varchar(8))
AS
SET DATEFORMAT dmy
delete WoolAnnual
where IDSheepGoat = @IDSheepGoat and DateShearAnnl = CAST(@DateShearAnnl AS smalldatetime)
go

--spDelete_WoolAnnual_IDSheepGoatDateShearAnnl "¿¡0000", "31.12.99"
--go