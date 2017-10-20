USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_Cert_ApprAge_YrAllExec" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_Cert_ApprAge_YrAllExec
GO
CREATE PROCEDURE spSelectInto_Cert_ApprAge_YrAllExec (@IDSheepGoat char(6)) AS
    DECLARE @Count tinyint, @CountMl tinyint, @CountFm tinyint, @CountSex tinyint
    DECLARE @IDSexMl char(1), @IDSex char(1)
--    SET DATEFORMAT dmy 
    SET @CountMl = 5 -- Count of records for a male.
    SET @CountFm = 2 -- Count of records for a female.
    SET @IDSexMl  = "0" -- Male sex.
    SET @Count = (SELECT COUNT(IDSheepGoat) AS CountIDSheepGoat FROM Cert_Appraisal) 
    IF @Count = 0 -- Above: -- Count records in the Cert_Appraisal table.
	EXEC spSelectInto_Cert_ApprAge_YrAllEmpty -- Create an empty table.
    ELSE 
	BEGIN
	SET @IDSex = (SELECT IDSex FROM Cert_SheepGoat WHERE IDSheepGoat = IDSheepGoat) -- Define 
	IF @IDSex = @IDSexMl					-- the sex record count (2 or 5).
	    SET @CountSex = @CountMl -- Male.
	ELSE
	    SET @CountSex = @CountFm -- Female.
	EXEC spSelectInto_Cert_ApprAge_YrAllFull @Count, @CountSex -- Create with avaialable rec.
	EXEC spSelectInto_Cert_ApprAge_YrAllAlt -- Allow nulls in the Cert_ApprAge_YrAll table.
	IF @Count < @CountSex -- Insert up to sex-relevant-number of records.
	    EXEC spSelectInto_Cert_ApprAge_YrAllIns @IDSheepGoat, @Count, @CountSex
	END
GO
spSelectInto_Cert_ApprAge_YrAllExec "ÀÀ0000"
GO
SELECT * FROM Cert_ApprAge_YrAll
GO