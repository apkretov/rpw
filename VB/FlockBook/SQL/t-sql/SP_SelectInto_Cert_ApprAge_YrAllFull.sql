USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_Cert_ApprAge_YrAllFull" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_Cert_ApprAge_YrAllFull
GO
CREATE PROCEDURE spSelectInto_Cert_ApprAge_YrAllFull (@Count tinyint, @CountSex tinyint) AS
    DECLARE @IDSheepGoat char(6)
    DECLARE @I tinyint, @J tinyint
    SET DATEFORMAT dmy 
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "Cert_ApprAge_YrAll" AND type = "U")
	DROP TABLE Cert_ApprAge_YrAll  -- Drop the previous table.
    SELECT Cert_Appraisal.IDSheepGoat, Cert_Appraisal.Age, Cert_Appraisal.DateAppr, -- Create a 
	Cert_Appraisal.Leng, (Diameter.DiamFrom + Diameter.DiamTo) / 2 AS Diam,     -- new table.
	Cert_Appraisal.Mass, Cert_Appraisal.Crimpins, Cert_Appraisal.Evens, 
	Cert_Appraisal.Density, Cert_Appraisal.Strength, WlGrsColour.Colour, 
	Cert_Appraisal.Quality, FluffColour.FluffColour, Cert_Appraisal.Fluff, 
	Cert_Appraisal.FibreYield, Cert_Appraisal.BodyType, Cert_Appraisal.Constitutn, 
	Cert_Appraisal.BodySize, Cert_Appraisal.FatTail
	INTO Cert_ApprAge_YrAll
	FROM WlGrsColour 
	    INNER JOIN Cert_Appraisal ON WlGrsColour.IDColour = Cert_Appraisal.IDColour 
	    INNER JOIN FluffColour ON Cert_Appraisal.IDFluffColour = FluffColour.IDFluffColour 
	    INNER JOIN Diameter ON Cert_Appraisal.Diam = Diameter.Diam
    SET @I = 0
    WHILE @I < @Count -- Loop as many as the number of records.
	BEGIN
	SET @I = @I + 1
	SET @J = 0
	WHILE @J < @CountSex/* - 1*/ -- Loop to look for records to shift. 
	    BEGIN
	    SET @J = @J + 1 --Below: -- Shift.
	    IF NOT EXISTS(SELECT IDSheepGoat FROM Cert_ApprAge_YrAll WHERE Age = @I) 
		BEGIN
		UPDATE Cert_ApprAge_YrAll
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
spSelectInto_Cert_ApprAge_YrAllFull 1, 2
GO
SELECT * FROM Cert_ApprAge_YrAll
GO