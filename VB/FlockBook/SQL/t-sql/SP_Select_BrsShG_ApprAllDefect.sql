USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_BrsShG_ApprAllDefect" AND type = "P")
    DROP PROCEDURE spSelect_BrsShG_ApprAllDefect
GO
CREATE PROCEDURE spSelect_BrsShG_ApprAllDefect (@IDFarm char(2), @DateDispMin int, 
    @DateDispMax int) AS
--    SET DATEFORMAT dmy
    SELECT SheepGoat.IDFarm, Appraisal.IDSheepGoat, Appraisal.Age, Appraisal.DateAppr, 
	Appraisal.Leng, Appraisal.Diam, Appraisal.Mass, Appraisal.Crimpins, Appraisal.Evens, 
	Appraisal.Density, Appraisal.Strength, WlGrsColour.Colour, Appraisal.Quality, 
	FluffColour.FluffColour, Appraisal.Fluff, Appraisal.FibreYield, Appraisal.BodyType, 
	Appraisal.Constitutn, Appraisal.BodySize, Appraisal.FatTail, Defects.Defect
	FROM WlGrsColour 
	    INNER JOIN Appraisal 
	    INNER JOIN SheepGoat ON 
    		Appraisal.IDSheepGoat = SheepGoat.IDSheepGoat ON 
    		WlGrsColour.IDColour = Appraisal.IDColour 
	    INNER JOIN FluffColour ON 
    		Appraisal.IDFluffColour = FluffColour.IDFluffColour 
	    LEFT OUTER JOIN Defects 
	    INNER JOIN InhertDefect ON 
    		Defects.IDDefect = InhertDefect.IDDefect ON 
    		Appraisal.IDSheepGoat = InhertDefect.IDSheepGoat AND 
		Appraisal.Age = InhertDefect.Age
	WHERE ((SheepGoat.IDFarm = @IDFarm) AND 
	    (SheepGoat.DateDisp >= @DateDispMin) AND 
	    (SheepGoat.DateDisp <= @DateDispMax))
GO
spSelect_BrsShG_ApprAllDefect "ÀÀ", 0, 65500 -- All.
--spSelect_BrsShG_ApprAllDefect "ÀÀ", 0, 0 -- Kept.
--spSelect_BrsShG_ApprAllDefect "ÀÀ", 1, 65500 -- Disposed.
GO	