use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spUpdate_WoolAnnual_IDSheepGoatDateShearAnnl" AND type = "P")
DROP PROCEDURE spUpdate_WoolAnnual_IDSheepGoatDateShearAnnl
GO

CREATE PROCEDURE spUpdate_WoolAnnual_IDSheepGoatDateShearAnnl_Prev0 (@IDSheepGoat char(6), 
	@DateShearAnnlOrigin varchar(8), @DateShearAnnl varchar(8), @GreaseAnnl real, @Leng real,
	@Diam real, @Age1Yr bit)
AS
SET DATEFORMAT dmy
update WoolAnnual
set DateShearAnnl = CAST(@DateShearAnnl AS smalldatetime), GreaseAnnl = @GreaseAnnl, 
	Leng = @Leng, Diam = @Diam, Age1Yr = @Age1Yr
where IDSheepGoat = @IDSheepGoat and DateShearAnnl = CAST(@DateShearAnnlOrigin AS smalldatetime)
go

--spUpdate_WoolAnnual_IDSheepGoatDateShearAnnl "¿¡0000", "31.12.99", "15.02.02", 5, 7, 20, 0
--go