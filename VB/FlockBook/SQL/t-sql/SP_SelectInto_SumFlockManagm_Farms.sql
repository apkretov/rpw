use FlockBook
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelectInto_SumFlockManagm_Farms" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_Farms
GO

CREATE PROCEDURE spSelectInto_SumFlockManagm_Farms (@IDFarm char(2))
AS
-- Drop the previous table.
if exists (select * from sysobjects where id = object_id(N'SumFlockManagm_Farms') 
	and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table SumFlockManagm_Farms
-- Create a new one.
select IDFarm, IDPersFarmer into SumFlockManagm_Farms 
	from Farms	
where IDFarm = @IDFarm
go

spSelectInto_SumFlockManagm_Farms "¿¿"
go
select * from SumFlockManagm_Farms
go