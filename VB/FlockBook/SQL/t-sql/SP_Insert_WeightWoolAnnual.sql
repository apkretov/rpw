--USE Test
USE FlockBookRec
GO
CREATE PROCEDURE spInsert_WeightWoolAnnual (@IDSheepGoat char(6), 
	@DateWtAnnl smalldatetime)
AS
INSERT INTO WeightWoolAnnual
(IDSheepGoat, DateWtAnnl, WtAnnl, DateShearAnnl, GreaseAnnl)
VALUES (@IDSheepGoat, @DateWtAnnl, 60, getdate(), 4)
GO


