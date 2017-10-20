USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_FrmInvMat" AND type = "P")
    DROP PROCEDURE spSelectInto_FrmInvMat
GO
CREATE PROCEDURE spSelectInto_FrmInvMat (@IDFarm char(2), @Date smalldatetime/*varchar(8)*/) AS 
    DECLARE @DateConv smalldatetime
    DECLARE @IDSexFm char(1)
    DECLARE @AgeMatMinDam smallint
    --SET DATEFORMAT dmy
    SET @DateConv = /*CAST(*/@Date /*AS smalldatetime)*/ -- Convert the date.
    SET @IDSexFm = "1" -- Female sex. 			
    SELECT @AgeMatMinDam = AgeMatMinDam FROM ContrlParam -- Minimal dam's mating age.
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "FrmInvMat" AND type = "U")
    	DROP TABLE FrmInvMat -- Drop the previous table.
    SELECT SheepGoat.IDFarm, SheepGoat.IDSheepGoat, Sex.Sex, SheepGoat.BreedCross,  -- Create a 
    	SheepGoat.DateBirth, SheepGoat.TypeBirth, SheepGoat.IDSire, SheepGoat.IDDam -- new one.
	INTO FrmInvMat
	FROM SheepGoat INNER JOIN Sex ON SheepGoat.IDSex = Sex.IDSex
	WHERE (SheepGoat.IDDispReas = "-") AND
	    (SheepGoat.IDFarm = @IDFarm) AND 
	    (SheepGoat.IDSex = @IDSexFm) AND
	    (SheepGoat.DateBirth + @AgeMatMinDam <= @DateConv)
GO
spSelectInto_FrmInvMat "ÀÀ", "01.01.00"
GO
SELECT * FROM FrmInvMat
GO