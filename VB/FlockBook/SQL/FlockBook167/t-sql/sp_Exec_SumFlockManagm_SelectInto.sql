USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects 
    WHERE NAME = "spExec_SumFlockManagm_SelectInto" AND type = "P") -- Drop the previous SP.
    DROP PROCEDURE spExec_SumFlockManagm_SelectInto
GO
CREATE PROCEDURE spExec_SumFlockManagm_SelectInto (@IDFarm char(2), @DateBegin varchar(8), 
	@DateEnd varchar(8)) AS -- Create a new one.
    EXEC spSelectInto_SumFlockManagm_Farms @IDFarm
    EXEC spSelectInto_SumFlockManagm_Mate @IDFarm, @DateBegin, @DateEnd
    EXEC spSelectInto_SumFlockManagm_LambKid
    EXEC spSelectInto_SumFlockManagm_Offspring
    EXEC spSelectInto_SumFlockManagm_LambKidWeaned @IDFarm, @DateBegin, @DateEnd
    EXEC spSelectInto_SumFlockManagm_WoolAnnl @IDFarm, @DateBegin, @DateEnd 
    EXEC spSelectInto_SumFlockManagm_Appraisal @IDFarm, @DateBegin, @DateEnd
    EXEC spSelectInto_SumFlockManagm_WeightWean @IDFarm, @DateBegin, @DateEnd
    EXEC spSelectInto_SumFlockManagm_Weight7Mon @IDFarm, @DateBegin, @DateEnd 
    EXEC spSelectInto_SumFlockManagm_WeightAnnl @IDFarm, @DateBegin, @DateEnd
    EXEC spSelectInto_SumFlockManagm_SheepGoat @IDFarm, @DateEnd
    EXEC spAlter_SumFlockManagm_SheepGoat
    EXEC spUpdate_SumFlockManagm_SheepGoat @DateEnd
    EXEC spSelectInto_SumFlockManagm_SheepGoatDisp @IDFarm, @DateBegin, @DateEnd
    EXEC spAlter_SumFlockManagm_SheepGoatDisp
    EXEC spUpdate_SumFlockManagm_SheepGoatDisp
    EXEC spSelectInto_SumFlockManagm_LambKidCount
    EXEC spSelectInto_SumFlockManagm_Disp_TotalDisp
GO
spExec_SumFlockManagm_SelectInto "¿¿", "01.01.90", "24.02.03"
GO