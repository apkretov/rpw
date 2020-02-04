use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spInsert_Weight7Mon" AND type = "P")
DROP PROCEDURE spInsert_Weight7Mon
GO

CREATE PROCEDURE spInsert_Weight7Mon (@IDLambKid char(6), @Date7Mon varchar(8), @Wt7Mon real)
AS
SET DATEFORMAT dmy
INSERT INTO Weight7Mon (IDLambKid, Date7Mon, Wt7Mon)
VALUES (@IDLambKid, CAST(@Date7Mon AS smalldatetime), @Wt7Mon/10)
go

--spInsert_Weight7Mon "¿¡0000", "01.01.01", 65.3
--go