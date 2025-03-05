USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelect_Appraisal_IDShGAge" AND type = "P")
    DROP PROCEDURE spSelect_Appraisal_IDShGAge
GO
CREATE PROCEDURE spSelect_Appraisal_IDShGAge (@IDSheepGoat char(6), @Age tinyint) AS
    SELECT Appraisal.IDSheepGoat, Appraisal.Age, Appraisal.DateAppr, ISNULL(Appraisal.Leng, 0) 
	AS Leng, Appraisal.Diam, Appraisal.Mass, Appraisal.Crimpins, Appraisal.Evens, 
	ISNULL(Appraisal.Density, 0) AS Density, Appraisal.Strength, Appraisal.IDColour, 
	WlGrsColour.Colour, Appraisal.Quality, Appraisal.IDFluffColour, FluffColour.FluffColour, 
	ISNULL(Appraisal.Fluff, 0) AS Fluff, ISNULL(Appraisal.FibreYield, 0) AS FibreYield, 
	Appraisal.BodyType, Appraisal.Constitutn, Appraisal.BodySize, Appraisal.FatTail
	FROM Appraisal 
	    INNER JOIN WlGrsColour ON 
    		Appraisal.IDColour = WlGrsColour.IDColour 
	    INNER JOIN FluffColour ON 
    		Appraisal.IDFluffColour = FluffColour.IDFluffColour
	WHERE IDSheepGoat = @IDSheepGoat AND
	    Age = @Age
GO
spSelect_Appraisal_IDShGAge "юб0001", 1
GO