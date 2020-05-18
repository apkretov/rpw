USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_CertRamHegoat_BV_Appr" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_CertRamHegoat_BV_Appr
GO
CREATE PROCEDURE spSelectInto_CertRamHegoat_BV_Appr @IDSire char(6) AS
    SET DATEFORMAT dmy
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "CertRamHegoat_BV_Appr" AND 
    type = "U")
        DROP TABLE CertRamHegoat_BV_Appr 
    SELECT DISTINCT SumGenEval_ApprSire.IDSire, SumGenEval_ApprSire.AvgLeng -  -- Create a new 
	SumGenEvalV_ApprFarm.AvgLeng AS BVLeng, SumGenEval_ApprSire.CountLeng, -- one.
	SumGenEval_ApprSire.AvgDiam - SumGenEvalV_ApprFarm.AvgDiam AS BVDiam, 
	SumGenEval_ApprSire.CountDiam 
	INTO CertRamHegoat_BV_Appr 
	FROM SumGenEval_ApprSire 
	    INNER JOIN SumGenEvalV_ApprFarm ON 
    		SumGenEval_ApprSire.IDFarm = SumGenEvalV_ApprFarm.IDFarm AND 
    		SumGenEval_ApprSire.BreedCross = SumGenEvalV_ApprFarm.BreedCross
	WHERE IDSire = @IDSire
GO
spSelectInto_CertRamHegoat_BV_Appr "¿¿0000"
GO
SELECT * FROM CertRamHegoat_BV_Appr
GO
