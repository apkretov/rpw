USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE -- Drop the previous SP.
	NAME = "spExec_SumFlockManagm_PerfSexAge" AND type = "P")
DROP PROCEDURE spExec_SumFlockManagm_PerfSexAge
GO
CREATE PROCEDURE spExec_SumFlockManagm_PerfSexAge (@IDFarm char(2), 
    @DateBegin varchar(8), @DateEnd varchar(8)) -- Create a new one.
AS
EXEC spSelectInto_SumFlockManagm_PerfSexAge_FarmSexAge
EXEC spSelectInto_SumFlockManagm_PerfSexAge_WtBirth @IDFarm, @DateBegin, @DateEnd
EXEC spSelectInto_SumFlockManagm_PerfSexAge_WtMaxAge @DateBegin, @DateEnd
EXEC spSelectInto_SumFlockManagm_PerfSexAge_WoolMaxAge @DateBegin, @DateEnd
EXEC spSelectInto_SumFlockManagm_PerfSexAge_WtAnnl @DateEnd 
EXEC spSelectInto_SumFlockManagm_PerfSexAge_WoolAnnl @DateEnd
EXEC spSelectInto_SumFlockManagm_PerfSexAge
EXEC spAlter_SumFlockManagm_PerfSexAge
GO
spExec_SumFlockManagm_PerfSexAge "¿¿", "26.01.03", "27.01.03" 
GO