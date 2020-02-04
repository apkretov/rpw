USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_Cert_PerfAge_YrAllFull" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_Cert_PerfAge_YrAllFull
GO
CREATE PROCEDURE spSelectInto_Cert_PerfAge_YrAllFull (@Count tinyint) AS
    DECLARE @IDSheepGoat char(6)
    DECLARE @Count7 tinyint
    DECLARE @I tinyint, @J tinyint
    SET DATEFORMAT dmy 
    SET @Count7 = 7 
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "Cert_PerfAge_YrAll" AND type = "U")
	DROP TABLE Cert_PerfAge_YrAll 
    SELECT * -- Create a new table.
	INTO Cert_PerfAge_YrAll
	FROM Cert_WeightWoolAnnl 
    SET @I = 0
    WHILE @I < @Count -- Loop as many as the number of records.
	BEGIN
	SET @I = @I + 1
	SET @J = 0
	WHILE @J < @Count7/* - 1*/ -- Loop to look for records to shift. 
	    BEGIN
	    SET @J = @J + 1 --Below: -- Shift.
	    IF NOT EXISTS(SELECT IDSheepGoat FROM Cert_PerfAge_YrAll WHERE Age = @I) 
		BEGIN
		UPDATE Cert_PerfAge_YrAll
		    SET Age = Age - 1
		    WHERE Age > @I
		END
	    ELSE
		BREAK -- Exit the loop.
	    CONTINUE
	    END
	CONTINUE
	END
GO
spSelectInto_Cert_PerfAge_YrAllFull 2
GO
SELECT * FROM Cert_PerfAge_YrAll
GO