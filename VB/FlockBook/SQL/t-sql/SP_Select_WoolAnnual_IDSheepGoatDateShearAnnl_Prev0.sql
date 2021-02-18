use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelect_WoolAnnual_IDSheepGoatDateShearAnnl" AND type = "P")
DROP PROCEDURE spSelect_WoolAnnual_IDSheepGoatDateShearAnnl
GO

CREATE PROCEDURE spSelect_WoolAnnual_IDSheepGoatDateShearAnnl_Prev0 (@IDSheepGoat char(6), 
	@DateShearAnnl varchar(8))
AS
SET DATEFORMAT dmy
select * from WoolAnnual
where IDSheepGoat = @IDSheepGoat and DateShearAnnl = CAST(@DateShearAnnl AS smalldatetime)
go

--spSelect_WoolAnnual_IDSheepGoatDateShearAnnl "¿¡0000", "31.12.99"
--go