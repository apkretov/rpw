use FlockBookRec
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelectInto_SumPerform_Farms" AND type = "P")
DROP PROCEDURE spSelectInto_SumPerform_Farms
GO

CREATE PROCEDURE spSelectInto_SumPerform_Farms (@IDFarm char(2))
AS
-- Drop the previous table.
if exists (select * from sysobjects where id = object_id(N'SumPerform_Farms') 
	and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table SumPerform_Farms
-- Create a new one.
select IDFarm, IDPersFarmer into SumPerform_Farms 
	from Farms	
where IDFarm = @IDFarm
go

spSelectInto_SumPerform_Farms "¿¿"
go
select * from SumPerform_Farms
go