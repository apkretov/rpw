USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_CertRamHegoat_BV_Wool" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_CertRamHegoat_BV_Wool
GO
CREATE PROCEDURE spSelectInto_CertRamHegoat_BV_Wool @IDSire char(6) AS
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "CertRamHegoat_BV_Wool" AND type = "U")
        DROP TABLE CertRamHegoat_BV_Wool 
    SELECT DISTINCT SumGenEval_WoolSire.IDSire, SumGenEval_WoolSire.AvgGrease1Yr - 
	SumGenEvalV_WoolFarm.AvgGrease1Yr AS BVGrease1Yr, SumGenEval_WoolSire.CountGrease1Yr
	INTO CertRamHegoat_BV_Wool 
	FROM SumGenEvalV_WoolFarm 
	    INNER JOIN SumGenEval_WoolSire ON 
    		SumGenEvalV_WoolFarm.IDFarm = SumGenEval_WoolSire.IDFarm AND 
    		SumGenEvalV_WoolFarm.BreedCross = SumGenEval_WoolSire.BreedCross
	WHERE IDSire = @IDSire
GO
spSelectInto_CertRamHegoat_BV_Wool "¿¿0000"
GO
SELECT * FROM CertRamHegoat_BV_Wool
GO
