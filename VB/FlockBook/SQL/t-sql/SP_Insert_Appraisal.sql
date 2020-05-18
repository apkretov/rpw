USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spInsert_Appraisal" AND type = "P")
    DROP PROCEDURE spInsert_Appraisal
GO
CREATE PROCEDURE spInsert_Appraisal (@IDSheepGoat char(6), @Age tinyint, @DateAppr smalldatetime/*varchar(8)*/,
    @Leng real, @Diam char(2), @Mass char(2), @Crimpins char(2), @Evens char(2), @Density smallint, 
    @Strength char(1), @IDColour char(1), @Quality char(2), @IDFluffColour char(1), 
    @Fluff tinyint, @FibreYield tinyint, @BodyType char(2), @Constitutn char(2), 
    @BodySize char(2), @FatTail char(1)) AS
    --SET DATEFORMAT dmy
    IF @Leng = 0 -- Convert zeros to NULLs.
	SET @Leng = NULL
    IF @Density = 0
	SET @Density = NULL
    IF @Fluff = 0
	SET @Fluff = NULL
    IF @FibreYield = 0
	SET @FibreYield = NULL
    INSERT INTO Appraisal (IDSheepGoat, Age, DateAppr, Leng, Diam, Mass, Crimpins, 
	Evens, Density, Strength, IDColour, Quality, IDFluffColour, Fluff, FibreYield, BodyType, 
	Constitutn, BodySize, FatTail)
    VALUES (@IDSheepGoat, @Age, /*CAST(*/@DateAppr /*AS smalldatetime)*/, @Leng / 10, @Diam, @Mass, 
	@Crimpins, @Evens, @Density, @Strength, @IDColour, @Quality, @IDFluffColour, @Fluff, 
	@FibreYield, @BodyType,	@Constitutn, @BodySize, @FatTail)
GO
SELECT * FROM Appraisal WHERE IDSheepGoat = "юб0001"
GO
spInsert_Appraisal "юб0001", 1, "01.01.99", 0, "44", "-", "-", "-", 0, "-", "1", "-", "1", 0,
    0, "-", "-", "-", "-"
GO
SELECT * FROM Appraisal WHERE IDSheepGoat = "юб0001"
GO