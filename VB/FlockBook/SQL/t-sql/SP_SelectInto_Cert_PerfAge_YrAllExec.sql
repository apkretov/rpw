USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_Cert_PerfAge_YrAllExec" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_Cert_PerfAge_YrAllExec
GO
CREATE PROCEDURE spSelectInto_Cert_PerfAge_YrAllExec (@IDSheepGoat char(6)) AS
    DECLARE @Count tinyint, @Count7 tinyint
    --SET DATEFORMAT dmy 
    SET @Count7 = 7 -- Below: -- Count records in the Cert_WeightWoolAnnl table.
    SET @Count = (SELECT COUNT(IDSheepGoat) AS CountIDSheepGoat FROM Cert_WeightWoolAnnl 
	WHERE IDSheepGoat = @IDSheepGoat)
    IF @Count = 0 
	EXEC spSelectInto_Cert_PerfAge_YrAllEmpty -- Create an empty table.
    ELSE 
	BEGIN
	EXEC spSelectInto_Cert_PerfAge_YrAllFull @Count -- Create a table with avaialable records
	--EXEC spSelectInto_Cert_PerfAge_YrAllAlt -- Allow nulls in the Cert_PerfAge_YrAll table.
	--EXEC spSelectInto_Cert_PerfAge_YrAllUpd -- Nullify zeros in the Cert_PerfAge_YrAll.
	IF @Count < @Count7 -- Insert up to 7 records.
	    EXEC spSelectInto_Cert_PerfAge_YrAllIns @IDSheepGoat, @Count 
	END
GO
spSelectInto_Cert_PerfAge_YrAllExec "ÀÀ0001"
GO
SELECT * FROM Cert_PerfAge_YrAll
GO