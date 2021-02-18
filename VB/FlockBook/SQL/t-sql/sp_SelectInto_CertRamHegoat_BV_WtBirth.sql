USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_CertRamHegoat_BV_WtBirth" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_CertRamHegoat_BV_WtBirth
GO
CREATE PROCEDURE spSelectInto_CertRamHegoat_BV_WtBirth @IDSire char(6) AS
--    SET DATEFORMAT dmy
IF EXISTS (SELECT name FROM sysobjects WHERE name = "CertRamHegoat_BV_WtBirth" AND type = "U")
    DROP TABLE CertRamHegoat_BV_WtBirth 
    SELECT DISTINCT SumGenEval_WtBirthSire.IDSire, 
        SumGenEval_WtBirthSire.AvgWtBirth - SumGenEvalV_WtBirthFarm.AvgWtBirth AS BVWtBirth, 
	SumGenEval_WtBirthSire.CountWtBirth -- Create a new one.
	INTO CertRamHegoat_BV_WtBirth 
	FROM SumGenEval_WtBirthSire 
	    INNER JOIN SumGenEvalV_WtBirthFarm ON 
    		SumGenEval_WtBirthSire.IDFarm = SumGenEvalV_WtBirthFarm.IDFarm AND 
    		SumGenEval_WtBirthSire.BreedCross = SumGenEvalV_WtBirthFarm.BreedCross
	WHERE IDSire = @IDSire
GO
spSelectInto_CertRamHegoat_BV_WtBirth "¿¿0000"
GO
SELECT * FROM CertRamHegoat_BV_WtBirth
GO
