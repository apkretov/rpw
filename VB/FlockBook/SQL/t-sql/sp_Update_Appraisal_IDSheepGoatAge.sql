USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects 
    WHERE name = "spUpdate_Appraisal_IDSheepGoatAge" AND type = "P")
    DROP PROCEDURE spUpdate_Appraisal_IDSheepGoatAge
GO
CREATE PROCEDURE spUpdate_Appraisal_IDSheepGoatAge (@IDSheepGoat char(6), @Age tinyint, 
    @DateAppr smalldatetime/*varchar(8)*/, @Leng real, @Diam char(2), @Mass char(2), @Crimpins char(2), 
    @Evens char(2), @Density smallint, @Strength char(1), @IDColour char(1), @Quality char(2), 
    @IDFluffColour char(1), @Fluff tinyint, @FibreYield tinyint, @BodyType char(2), 
    @Constitutn char(2), @BodySize char(2), @FatTail char(1)) AS
    --SET DATEFORMAT dmy
    IF @Leng = 0 -- Convert zeros to NULLs.
	SET @Leng = NULL
    IF @Density = 0
	SET @Density = NULL
    IF @Fluff = 0
	SET @Fluff = NULL
    IF @FibreYield = 0
	SET @FibreYield = NULL
    UPDATE Appraisal
	SET DateAppr = /*CAST(*/@DateAppr /*AS smalldatetime)*/, Leng = @Leng / 10, Diam = @Diam, 
	    Mass = @Mass, Crimpins = @Crimpins, Evens = @Evens, Density = @Density, 
	    Strength = @Strength, IDColour = @IDColour, Quality = @Quality, 
	    IDFluffColour = @IDFluffColour, Fluff = @Fluff, FibreYield = @FibreYield, 
	    BodyType = @BodyType, Constitutn = @Constitutn, BodySize = @BodySize, 
	    FatTail = @FatTail 
	WHERE IDSheepGoat = @IDSheepGoat AND 
	    Age = @Age
GO
SELECT * FROM Appraisal
    WHERE IDSheepGoat = "юб0001"
GO
spUpdate_Appraisal_IDSheepGoatAge "юб0001", 1, "01.01.99", 0, "56", "-", "-", "-", 0, "-", "1", "-", "1", 0,
    0, "-", "-", "-", "-"
GO
SELECT * FROM Appraisal
    WHERE IDSheepGoat = "юб0001"
GO