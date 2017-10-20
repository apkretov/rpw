USE FlockBookRec
--USE Test
GO

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spInsert_TransFarm" AND type = "P")
DROP PROCEDURE spInsert_TransFarm
GO

CREATE PROCEDURE spInsert_TransFarm (@IDSheepGoat char(6), 
	@DateTrans varchar(8), @IDFarm char(2))
AS
SET DATEFORMAT dmy
INSERT INTO TransFarm(IDSheepGoat, DateTrans, IDFarm)
VALUES (@IDSheepGoat, CAST(@DateTrans AS smalldatetime), @IDFarm)
GO