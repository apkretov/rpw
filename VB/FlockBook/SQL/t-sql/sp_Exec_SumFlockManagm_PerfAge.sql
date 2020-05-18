USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE -- Drop the previous SP.
	NAME = "spExec_SumFlockManagm_PerfAge" AND type = "P")
DROP PROCEDURE spExec_SumFlockManagm_PerfAge
GO
CREATE PROCEDURE spExec_SumFlockManagm_PerfAge -- Create a new one.
AS
EXEC spSelectInto_SumFlockManagm_PerfAge_WeightAge
EXEC spSelectInto_SumFlockManagm_PerfAge_GreaseAge
EXEC spSelectInto_SumFlockManagm_PerfAge_WeightGroup
EXEC spSelectInto_SumFlockManagm_PerfAge_GreaseGroup
EXEC spSelectInto_SumFlockManagm_PerfAge
GO
spExec_SumFlockManagm_PerfAge 
GO