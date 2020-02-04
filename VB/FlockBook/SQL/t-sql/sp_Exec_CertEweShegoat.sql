USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects -- Drop the previous SP.
    WHERE name = "spExec_CertEweShegoat" AND type = "P")
    DROP PROCEDURE spExec_CertEweShegoat
GO
CREATE PROCEDURE spExec_CertEweShegoat @IDSheepGoat char(6) AS -- Create a new one.
    EXEC spSelectInto_Cert_SheepGoat @IDSheepGoat
    EXEC spSelectInto_Cert_SheepGoatSire
    EXEC spSelectInto_Cert_SheepGoatDam
    EXEC spUpdate_Cert @IDSheepGoat 
    EXEC spSelectInto_CertEweShegoat_LambKid @IDSheepGoat 
    EXEC spSelectInto_CertEweShegoat_Offspring @IDSheepGoat 
    EXEC spSelectInto_Cert_WeightWoolAnnl @IDSheepGoat
    EXEC spSelectInto_Cert_PerfAge_YrAllExec @IDSheepGoat 
    EXEC spSelectInto_Cert_Appraisal @IDSheepGoat 
    EXEC spSelectInto_Cert_ApprAge_YrAllExec @IDSheepGoat 
GO
spExec_CertEweShegoat "¿¿0021"
GO
