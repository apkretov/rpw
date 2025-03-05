USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_Cert_ApprAge_YrAllEmpty" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_Cert_ApprAge_YrAllEmpty
GO
CREATE PROCEDURE spSelectInto_Cert_ApprAge_YrAllEmpty AS
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "Cert_ApprAge_YrAll" AND type = "U")
	DROP TABLE Cert_ApprAge_YrAll 
    SELECT Cert_WeightWoolAnnlAge.IDSheepGoat, Cert_WeightWoolAnnlAge.Age, --Create an empty tab.
	Cert_Appraisal.DateAppr, Cert_Appraisal.Leng, (Diameter.DiamFrom + Diameter.DiamTo) / 2 
	AS Diam, Cert_Appraisal.Mass, Cert_Appraisal.Crimpins, Cert_Appraisal.Evens, 
	Cert_Appraisal.Density, Cert_Appraisal.Strength, WlGrsColour.Colour, 
    	Cert_Appraisal.Quality, FluffColour.FluffColour, Cert_Appraisal.Fluff, 
	Cert_Appraisal.FibreYield, Cert_Appraisal.BodyType, Cert_Appraisal.Constitutn, 
    	Cert_Appraisal.BodySize, Cert_Appraisal.FatTail
	INTO Cert_ApprAge_YrAll
	FROM WlGrsColour INNER JOIN Cert_Appraisal ON 
	    	WlGrsColour.IDColour = Cert_Appraisal.IDColour 
	    INNER JOIN FluffColour ON 
	    	Cert_Appraisal.IDFluffColour = FluffColour.IDFluffColour 
	    INNER JOIN Diameter ON 
	    	Cert_Appraisal.Diam = Diameter.Diam 
	    RIGHT OUTER JOIN Cert_WeightWoolAnnlAge ON 
	    	Cert_Appraisal.Age = Cert_WeightWoolAnnlAge.Age
GO
spSelectInto_Cert_ApprAge_YrAllEmpty
GO
SELECT * FROM Cert_ApprAge_YrAll
GO
