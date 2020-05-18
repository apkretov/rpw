use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spDelete_WeightWoolAnnl_IDSheepGoatAge" AND type = "P")
DROP PROCEDURE spDelete_WeightWoolAnnl_IDSheepGoatAge
GO

CREATE PROCEDURE spDelete_WeightWoolAnnl_IDSheepGoatAge (@IDSheepGoat char(6), 
	@Age tinyint)
AS
delete WeightWoolAnnl
where IDSheepGoat = @IDSheepGoat and Age = @Age
go

spDelete_WeightWoolAnnl_IDSheepGoatAge "¿¡0000", 1
go