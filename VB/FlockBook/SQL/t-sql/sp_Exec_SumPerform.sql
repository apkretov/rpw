USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spExec_SumPerform" AND 
    type = "P") -- Drop the previous SP.
    DROP PROCEDURE spExec_SumPerform
GO
CREATE PROCEDURE spExec_SumPerform (@IDFarm char(2), @Date varchar(8)) AS -- Create a new one.
    EXEC spSelectInto_SumPerform_Farms @IDFarm
    EXEC spSelectInto_SumPerform_SheepGoat @IDFarm, @Date
    EXEC spAlter_SumPerform_SheepGoat
    EXEC spUpdate_SumPerform_SheepGoat @Date
    EXEC spSelectInto_SumPerform_WeightWean @Date
    EXEC spSelectInto_SumPerform_Weight7Mon @Date
    EXEC spSelectInto_SumPerform_WeightWoolAnnl @Date
    EXEC spSelectInto_SumPerform_Appraisal @Date
    EXEC spSelectInto_SumPerform_MaxAge @Date
GO
spExec_SumPerform "¿¿", "29.01.02"
GO