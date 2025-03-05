use FlockBookRec
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spDropTable_SumPerform" AND type = "P")
DROP PROCEDURE spDropTable_SumPerform
GO

CREATE PROCEDURE spDropTable_SumPerform
AS
-- Drop the SumPerform_Farms table.
if exists (select * from sysobjects where id = object_id(N'SumPerform_Farms') 
	and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table SumPerform_Farms
-- Drop the SumPerform_Farms table.
if exists (select * from sysobjects where id = object_id(N'SumPerform_SheepGoat') 
	and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table SumPerform_SheepGoat
go

spDropTable_SumPerform
go