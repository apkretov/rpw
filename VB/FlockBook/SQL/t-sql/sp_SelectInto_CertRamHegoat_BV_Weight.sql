USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_CertRamHegoat_BV_Weight" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_CertRamHegoat_BV_Weight
GO
CREATE PROCEDURE spSelectInto_CertRamHegoat_BV_Weight @IDSire char(6) AS
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "CertRamHegoat_BV_Weight" AND type = "U")
        DROP TABLE CertRamHegoat_BV_Weight 
    SELECT DISTINCT SumGenEval_WeightSire.IDSire, SumGenEval_WeightSire.AvgWt1Yr - 
	SumGenEvalV_WeightFarm.AvgWt1Yr AS BVWt1Yr, SumGenEval_WeightSire.CountWt1Yr
	INTO CertRamHegoat_BV_Weight 
	FROM SumGenEvalV_WeightFarm 
	    INNER JOIN SumGenEval_WeightSire ON 
    		SumGenEvalV_WeightFarm.IDFarm = SumGenEval_WeightSire.IDFarm AND 
    		SumGenEvalV_WeightFarm.BreedCross = SumGenEval_WeightSire.BreedCross
	WHERE IDSire = @IDSire
GO
spSelectInto_CertRamHegoat_BV_Weight "¿¿0000"
GO
SELECT * FROM CertRamHegoat_BV_Weight
GO
