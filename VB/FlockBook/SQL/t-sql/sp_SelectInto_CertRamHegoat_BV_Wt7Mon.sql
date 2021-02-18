USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_CertRamHegoat_BV_Wt7Mon" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_CertRamHegoat_BV_Wt7Mon
GO
CREATE PROCEDURE spSelectInto_CertRamHegoat_BV_Wt7Mon @IDSire char(6) AS
    SET DATEFORMAT dmy
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "CertRamHegoat_BV_Wt7Mon" AND type = "U")
        DROP TABLE CertRamHegoat_BV_Wt7Mon 
    SELECT DISTINCT SumGenEval_Wt7MonSire.IDSire, 
	SumGenEval_Wt7MonSire.AvgWt7Mon - SumGenEvalV_Wt7MonFarm.AvgWt7Mon AS BVWt7Mon, 
	SumGenEval_Wt7MonSire.CountWt7Mon -- Create a new one.
	INTO CertRamHegoat_BV_Wt7Mon 
	FROM SumGenEval_Wt7MonSire 
	    INNER JOIN SumGenEvalV_Wt7MonFarm ON 
    		SumGenEval_Wt7MonSire.IDFarm = SumGenEvalV_Wt7MonFarm.IDFarm AND 
    		SumGenEval_Wt7MonSire.BreedCross = SumGenEvalV_Wt7MonFarm.BreedCross
	WHERE IDSire = @IDSire
GO
SELECT * FROM CertRamHegoat_BV_Wt7Mon
GO
