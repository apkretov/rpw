USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE -- Drop the previous SP.
	NAME = "spSelectInto_SumFlockManagm_BearDistr" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_BearDistr
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_BearDistr -- Create a new one.
AS
EXEC spSelectInto_SumFlockManagm_BearDistr_AllAge
EXEC spSelectInto_SumFlockManagm_BearDistr1
EXEC spSelectInto_SumFlockManagm_BearDistr2
GO
spSelectInto_SumFlockManagm_BearDistr 
GO

