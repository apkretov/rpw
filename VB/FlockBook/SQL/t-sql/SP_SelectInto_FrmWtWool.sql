USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_FrmWtWool" AND type = "P")
    DROP PROCEDURE spSelectInto_FrmWtWool
GO
CREATE PROCEDURE spSelectInto_FrmWtWool (@IDFarm char(2), @Date smalldatetime/*varchar(8)*/) AS 
    DECLARE @DateConv smalldatetime
    DECLARE @Age1YrWtMin smallint
    DECLARE @Age1YrShearMin smallint
    --SET DATEFORMAT dmy
    SET @DateConv = /*CAST(*/@Date /*AS smalldatetime)*/ -- Convert the date.
    SELECT @Age1YrWtMin = Age1YrWtMin FROM ContrlParam -- The minimal age at 1-yr wt.
    SELECT @Age1YrShearMin = Age1YrShearMin FROM ContrlParam -- The minimal age at 1-yr shearing.
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "FrmWtWool" AND type = "U")
    	DROP TABLE FrmWtWool
    SELECT SheepGoat.IDFarm, SheepGoat.IDSheepGoat, Sex.Sex
	INTO FrmWtWool
	FROM SheepGoat
	    INNER JOIN Sex ON SheepGoat.IDSex = Sex.IDSex
	WHERE (SheepGoat.IDDispReas = "-") AND
    	    (SheepGoat.IDFarm = @IDFarm) AND 
	    (@DateConv >= SheepGoat.DateBirth) AND -- Prevent arithmetic overflow.
	    ( ((@DateConv - SheepGoat.DateBirth) >= @Age1YrWtMin) OR -- Animals older than 1 yr 
	    ((@DateConv - SheepGoat.DateBirth) >= @Age1YrShearMin) ) -- at wt/shearing.
	ORDER BY SheepGoat.IDSex, SheepGoat.IDSheepGoat
GO
spSelectInto_FrmWtWool "¿¿", "01.01.99"
GO
SELECT * FROM FrmWtWool
GO