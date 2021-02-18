USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects 
    WHERE NAME = "spExec_SumFlockManagm_Reprod" AND type = "P") -- Drop the previous SP.
    DROP PROCEDURE spExec_SumFlockManagm_Reprod
GO
CREATE PROCEDURE spExec_SumFlockManagm_Reprod AS -- Create a new one.
    EXEC spSelectInto_SumFlockManagm_Reprod_AbortCount --@IDFarm
    EXEC spSelectInto_SumFlockManagm_Reprod_OffspBornCount 
    EXEC spSelectInto_SumFlockManagm_Reprod 
GO
spExec_SumFlockManagm_Reprod
GO