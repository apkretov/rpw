USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_FrmWtLmK" AND type = "P")
    DROP PROCEDURE spSelectInto_FrmWtLmK
GO
CREATE PROCEDURE spSelectInto_FrmWtLmK (@IDFarm char(2), @Date varchar(8)) AS 
    DECLARE @DateConv smalldatetime
    DECLARE @Age1YrWtMin smalldatetime --smallint
    SET DATEFORMAT dmy
    SET @DateConv = CAST(@Date AS smalldatetime) -- Convert the date.
    SELECT @Age1YrWtMin = Age1YrWtMin FROM ContrlParam -- The minimal age at 1-yr wt.
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "FrmWtLmK" AND type = "U")
    	DROP TABLE FrmWtLmK
    SELECT SheepGoat.IDFarm, Offspring.IDLambKid, SexOffspring.Sex
	INTO FrmWtLmK
	FROM Offspring 
	    INNER JOIN SexOffspring ON 
	    	Offspring.IDSex = SexOffspring.IDSex 
	    INNER JOIN SheepGoat ON 
		Offspring.IDLambKid = SheepGoat.IDSheepGoat
	WHERE (Offspring.IDLambKid <> "-") AND 
	    (SheepGoat.IDDispReas = "-") AND
    	    (SheepGoat.IDFarm = @IDFarm) AND 
	    (@DateConv >= SheepGoat.DateBirth) AND -- Prevent arithmetic overflow.
	    ((@DateConv - SheepGoat.DateBirth) < @Age1YrWtMin) -- Offspring younger than 1 yr.
	ORDER BY SheepGoat.IDSex
GO
spSelectInto_FrmWtLmK "ÀÀ", "01.06.00" 
GO
SELECT * FROM FrmWtLmK
GO