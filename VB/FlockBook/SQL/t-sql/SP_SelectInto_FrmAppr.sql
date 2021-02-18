USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_FrmAppr" AND type = "P")
    DROP PROCEDURE spSelectInto_FrmAppr
GO
CREATE PROCEDURE spSelectInto_FrmAppr (@IDFarm char(2), @Date smalldatetime/*varchar(8)*/) AS 
    DECLARE @DateConv smalldatetime
    DECLARE @Age1YrShearMin smallint
    --SET DATEFORMAT dmy
    SET @DateConv = /*CAST(*/@Date /*AS smalldatetime)*/ -- Convert the date.
    SELECT @Age1YrShearMin = Age1YrShearMin FROM ContrlParam -- The minimal age at 1-yr shearing.
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "FrmAppr" AND type = "U")
    	DROP TABLE FrmAppr
    SELECT SheepGoat.IDFarm, SheepGoat.IDSheepGoat, Sex.Sex
	INTO FrmAppr
	FROM SheepGoat
	    INNER JOIN Sex ON SheepGoat.IDSex = Sex.IDSex
	WHERE (SheepGoat.IDDispReas = "-") AND
    	    (SheepGoat.IDFarm = @IDFarm) AND 
	    (@DateConv >= SheepGoat.DateBirth) AND -- Prevent arithmetic overflow.
	    ((@DateConv - SheepGoat.DateBirth) >= @Age1YrShearMin) -- Animals older than 1 yr at 
	ORDER BY SheepGoat.IDSex, SheepGoat.IDSheepGoat				   -- shearing.
GO								   
spSelectInto_FrmAppr "¿¿", "01.01.99"
GO
SELECT * FROM FrmAppr
GO