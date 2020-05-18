USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_Cert_PerfAge_YrAllIns" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_Cert_PerfAge_YrAllIns
GO
CREATE PROCEDURE spSelectInto_Cert_PerfAge_YrAllIns (@IDSheepGoat char(6), @Count tinyint) AS
--    DECLARE @IDSheepGoat char(6)
    DECLARE @Count7 tinyint
    DECLARE @I tinyint
    SET DATEFORMAT dmy 
    SET @Count7 = 7 
--    SET @IDSheepGoat = (SELECT IDSheepGoat FROM Cert_SheepGoat) -- Get IDSheepGoat.
    SET @I = 0
    WHILE @I < @Count7 - @Count -- Insert up to 7 records.
	BEGIN
	SET @I = @I + 1
	INSERT INTO Cert_PerfAge_YrAll (IDSheepGoat, Age)
	    VALUES (@IDSheepGoat, @Count + @I)
	END
GO
spSelectInto_Cert_PerfAge_YrAllIns "ÀÀ0000", 3
GO
SELECT * FROM Cert_PerfAge_YrAll
GO