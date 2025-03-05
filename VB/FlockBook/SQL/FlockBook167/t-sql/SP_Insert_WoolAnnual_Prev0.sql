use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spInsert_WoolAnnual" AND type = "P")
DROP PROCEDURE spInsert_WoolAnnual
GO

CREATE PROCEDURE spInsert_WoolAnnual_Prev0 (@IDSheepGoat char(6), @DateShearAnnl varchar(8), 
	@GreaseAnnl real, @Leng real, @Diam real, @Age1Yr bit)
AS
SET DATEFORMAT dmy
INSERT INTO WoolAnnual (IDSheepGoat, DateShearAnnl, GreaseAnnl, Leng, Diam, Age1Yr)
VALUES (@IDSheepGoat, CAST(@DateShearAnnl AS smalldatetime), @GreaseAnnl, @Leng, @Diam, @Age1Yr)
go

--spInsert_WoolAnnual "¿¡0000", "31.12.99", 12, 5, 30, 1
--go