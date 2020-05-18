USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_CertRamHegoat_BV_WtWean" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_CertRamHegoat_BV_WtWean
GO
CREATE PROCEDURE spSelectInto_CertRamHegoat_BV_WtWean @IDSire char(6) AS
    SET DATEFORMAT dmy
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "CertRamHegoat_BV_WtWean" AND 
    type = "U")
        DROP TABLE CertRamHegoat_BV_WtWean 
    SELECT DISTINCT SumGenEval_WtWeanSire.IDSire, 
        SumGenEval_WtWeanSire.AvgWtWean - SumGenEvalV_WtWeanFarm.AvgWtWean AS BVWtWean, 
        SumGenEval_WtWeanSire.CountWtWean -- Create a new one.
	INTO CertRamHegoat_BV_WtWean 
	FROM SumGenEval_WtWeanSire 
	    INNER JOIN SumGenEvalV_WtWeanFarm ON 
    		SumGenEval_WtWeanSire.IDFarm = SumGenEvalV_WtWeanFarm.IDFarm AND 
    		SumGenEval_WtWeanSire.BreedCross = SumGenEvalV_WtWeanFarm.BreedCross
	WHERE IDSire = @IDSire
GO
spSelectInto_CertRamHegoat_BV_WtWean "¿¿0000"
GO
SELECT * FROM CertRamHegoat_BV_WtWean
GO
