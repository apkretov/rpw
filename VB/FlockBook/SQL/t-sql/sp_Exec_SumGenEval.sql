USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spExec_SumGenEval" AND type = "P") 
    DROP PROCEDURE spExec_SumGenEval
GO
CREATE PROCEDURE spExec_SumGenEval (@IDFarm char(2), @Date smalldatetime) AS
    EXEC spSelectInto_SumGenEval_Farms @IDFarm
    EXEC spSelectInto_SumGenEval_FarmBrdSrOffsp @IDFarm, @Date
    EXEC spSelectInto_SumGenEval_WtBirth @Date
    EXEC spSelectInto_SumGenEval_WtBirthSire			
    EXEC spSelectInto_SumGenEval_WtWean @Date
    EXEC spSelectInto_SumGenEval_WtWeanSire
    EXEC spSelectInto_SumGenEval_Wt7Mon @Date 
    EXEC spSelectInto_SumGenEval_Wt7MonSire
    EXEC spSelectInto_SumGenEval_Weight @Date
    EXEC spSelectInto_SumGenEval_Wool @Date
    EXEC spSelectInto_SumGenEval_Appraisal @Date 
    EXEC spSelectInto_SumGenEval_WeightSire
    EXEC spSelectInto_SumGenEval_WoolSire 
    EXEC spSelectInto_SumGenEval_ApprSire 
GO
spExec_SumGenEval "¿¿", "01.01.03" -- "12/31/02"
GO