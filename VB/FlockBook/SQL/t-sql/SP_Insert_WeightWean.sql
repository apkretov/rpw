use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spInsert_WeightWean" AND type = "P")
DROP PROCEDURE spInsert_WeightWean
GO

CREATE PROCEDURE spInsert_WeightWean (@IDLambKid char(6), @DateWean varchar(8), @WtWean real)
AS
SET DATEFORMAT dmy
INSERT INTO WeightWean (IDLambKid, DateWean, WtWean)
VALUES (@IDLambKid, CAST(@DateWean AS smalldatetime), @WtWean/10)
go

--spInsert_WeightWean "¿¡0000", "01.01.01", 65.3
--go