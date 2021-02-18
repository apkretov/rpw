USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spExec_CertRamHegoat" AND type = "P") 
    DROP PROCEDURE spExec_CertRamHegoat
GO
CREATE PROCEDURE spExec_CertRamHegoat (@IDFarm char(2), @IDSheepGoat char(6), 
    @Date smalldatetime) AS
    EXEC spSelectInto_Cert_SheepGoat @IDSheepGoat
    EXEC spSelectInto_Cert_SheepGoatSire
    EXEC spSelectInto_Cert_SheepGoatDam 
    EXEC spUpdate_Cert @IDSheepGoat 
    EXEC spSelectInto_Cert_WeightWoolAnnl @IDSheepGoat
    EXEC spSelectInto_Cert_PerfAge_YrAllExec @IDSheepGoat 
    EXEC spSelectInto_Cert_Appraisal @IDSheepGoat
    EXEC spSelectInto_Cert_ApprAge_YrAllExec @IDSheepGoat
    EXEC spSelectInto_CertRamHegoat_SireOffspring @IDSheepGoat
    EXEC spSelectInto_CertRamHegoat_Mate @IDSheepGoat
--    IF EXISTS (SELECT * FROM CertRamHegoat_SireOffspring WHERE IDSire = @IDSheepGoat)
--	BEGIN -- Caclulate the BV, if there are offsprings.
    	EXEC spExec_SumGenEval @IDFarm, @Date 
    	EXEC spSelectInto_CertRamHegoat_BV_WtBirth @IDSheepGoat
    	EXEC spSelectInto_CertRamHegoat_BV_WtWean @IDSheepGoat
    	EXEC spSelectInto_CertRamHegoat_BV_Wt7Mon @IDSheepGoat
	EXEC spSelectInto_CertRamHegoat_BV_Weight @IDSheepGoat 
	EXEC spSelectInto_CertRamHegoat_BV_Wool @IDSheepGoat 
    	EXEC spSelectInto_CertRamHegoat_BV_Appr @IDSheepGoat
--	END
GO
spExec_CertRamHegoat "¿¿", "¿¡0002", "05.31.03" -- "12/31/02" -- "31/12/02"
GO