use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelect_WoolAnnual_IDSheepGoat" AND type = "P")
DROP PROCEDURE spSelect_WoolAnnual_IDSheepGoat
GO

CREATE PROCEDURE spSelect_WoolAnnual_IDSheepGoat_Prev0 (@IDSheepGoat char(6))
AS
SET DATEFORMAT dmy
select * from WoolAnnual
where IDSheepGoat = @IDSheepGoat
go

--spSelect_WoolAnnual_IDSheepGoat "¿¡0000"
--go