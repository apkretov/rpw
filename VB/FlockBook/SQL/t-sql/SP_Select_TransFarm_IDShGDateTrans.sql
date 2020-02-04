use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelect_TransFarm_IDShGDateTrans" AND type = "P")
DROP PROCEDURE spSelect_TransFarm_IDShGDateTrans
GO

CREATE PROCEDURE spSelect_TransFarm_IDShGDateTrans (@IDSheepGoat char(6), 
	@DateTrans varchar(8))
AS
SET DATEFORMAT dmy
select * from TransFarm
where IDSheepGoat = @IDSheepGoat and DateTrans = CAST(@DateTrans AS smalldatetime)
go