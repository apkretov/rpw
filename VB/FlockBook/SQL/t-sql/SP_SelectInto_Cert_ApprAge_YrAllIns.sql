USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_Cert_ApprAge_YrAllIns" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_Cert_ApprAge_YrAllIns
GO
CREATE PROCEDURE spSelectInto_Cert_ApprAge_YrAllIns (@IDSheepGoat char(6), @Count tinyint, 
    @CountSex tinyint) AS
    DECLARE @I tinyint
    SET DATEFORMAT dmy 
    SET @I = 0
    WHILE @I < @CountSex - @Count -- Insert up to 7 records.
	BEGIN
	SET @I = @I + 1
	INSERT INTO Cert_ApprAge_YrAll (IDSheepGoat, Age)
	    VALUES (@IDSheepGoat, @Count + @I)
	END
GO
spSelectInto_Cert_ApprAge_YrAllIns "ÀÀ0000", 2, 5
GO
SELECT * FROM Cert_ApprAge_YrAll
GO