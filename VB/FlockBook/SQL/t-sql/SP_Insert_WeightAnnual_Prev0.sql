use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spInsert_WeightAnnual" AND type = "P")
DROP PROCEDURE spInsert_WeightAnnual
GO

CREATE PROCEDURE spInsert_WeightAnnual_Prev0 (@IDSheepGoat char(6), @DateAnnl varchar(8), @WtAnnl real,
	@Age1Yr bit)
AS
SET DATEFORMAT dmy
INSERT INTO WeightAnnual (IDSheepGoat, DateAnnl, WtAnnl, Age1Yr)
VALUES (@IDSheepGoat, CAST(@DateAnnl AS smalldatetime), @WtAnnl, @Age1Yr)
go

--spInsert_WeightAnnual "¿¡0000", "01.01.01", 65.3, 1
--go