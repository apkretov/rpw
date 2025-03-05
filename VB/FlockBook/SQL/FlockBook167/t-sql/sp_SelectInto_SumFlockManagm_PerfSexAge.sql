USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE -- Drop the previous SP.
	name = "spSelectInto_SumFlockManagm_PerfSexAge" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_PerfSexAge
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_PerfSexAge -- Create a new one.
AS
--SET DATEFORMAT dmy
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_PerfSexAge" AND type = "U")
DROP TABLE SumFlockManagm_PerfSexAge
SELECT SumFlockManagm_PerfSexAge_FarmSexAge.IDFarm, 
    SumFlockManagm_PerfSexAge_FarmSexAge.IDAgeSex, 
    SumFlockManagm_PerfSexAge_FarmSexAge.AgeSex, 
    SumFlockManagmV_PerfSexAge_Avail.WtBirth, 
    SumFlockManagmV_PerfSexAge_Avail.WtWean, 
    SumFlockManagmV_PerfSexAge_Avail.Wt7Mon, 
    SumFlockManagmV_PerfSexAge_Avail.Wt1Yr, 
    SumFlockManagmV_PerfSexAge_Avail.WtAnnl, 
    SumFlockManagmV_PerfSexAge_Avail.Grease1Yr, 
    SumFlockManagmV_PerfSexAge_Avail.GreaseAnnl, 
    SumFlockManagmV_PerfSexAge_Avail.Leng, 
    SumFlockManagmV_PerfSexAge_Avail.Diam, 
    SumFlockManagmV_PerfSexAge_Avail.SelIndx
INTO SumFlockManagm_PerfSexAge 
FROM SumFlockManagmV_PerfSexAge_Avail RIGHT OUTER JOIN
    SumFlockManagm_PerfSexAge_FarmSexAge ON 
    SumFlockManagmV_PerfSexAge_Avail.IDAgeSex = 
    SumFlockManagm_PerfSexAge_FarmSexAge.IDAgeSex
GO
spSelectInto_SumFlockManagm_PerfSexAge 
GO
SELECT * FROM SumFlockManagm_PerfSexAge
GO