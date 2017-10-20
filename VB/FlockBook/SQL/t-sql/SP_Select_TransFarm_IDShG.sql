use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelect_TransFarm_IDShG" AND type = "P")
DROP PROCEDURE spSelect_TransFarm_IDShG
GO

CREATE PROCEDURE spSelect_TransFarm_IDShG (@IDSheepGoat char(6))
AS
select * from TransFarm
where IDSheepGoat = @IDSheepGoat
go

spSelect_TransFarm_IDShG "¿¡0008"
go
