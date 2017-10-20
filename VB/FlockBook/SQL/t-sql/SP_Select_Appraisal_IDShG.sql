USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelect_Appraisal_IDShG" AND type = "P")
    DROP PROCEDURE spSelect_Appraisal_IDShG
GO
CREATE PROCEDURE spSelect_Appraisal_IDShG (@IDSheepGoat char(6)) AS
    SELECT Appraisal.IDSheepGoat, Appraisal.Age, Appraisal.DateAppr, Appraisal.Leng, 
	Appraisal.Diam, Appraisal.Mass, Appraisal.Crimpins, Appraisal.Evens, Appraisal.Density, 
    	Appraisal.Strength, WlGrsColour.Colour, Appraisal.Quality, FluffColour.FluffColour, 
	Appraisal.Fluff, Appraisal.FibreYield, Appraisal.BodyType, Appraisal.Constitutn, 
	Appraisal.BodySize, Appraisal.FatTail
	FROM Appraisal 
	    INNER JOIN WlGrsColour ON 
    		Appraisal.IDColour = WlGrsColour.IDColour 
	    INNER JOIN FluffColour ON 
    		Appraisal.IDFluffColour = FluffColour.IDFluffColour
	WHERE IDSheepGoat = @IDSheepGoat
GO
spSelect_Appraisal_IDShG "¿¿0000"
GO