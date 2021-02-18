USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_SumPerform_SheepGoat" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_SumPerform_SheepGoat
GO
CREATE PROCEDURE spSelectInto_SumPerform_SheepGoat (@IDFarm char(2), @Date smalldatetime/*varchar(8)*/) AS
    DECLARE @DateEnd smalldatetime
    --SET DATEFORMAT dmy
    SET @DateEnd = /*CAST(*/@Date /*AS smalldatetime)*/
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumPerform_SheepGoat" AND type = "U") 
        DROP TABLE SumPerform_SheepGoat -- Drop the previous table.
    SELECT IDFarm, IDSheepGoat, IDSex, BreedCross, DateBirth, TypeBirth -- Create a new one.
        INTO SumPerform_SheepGoat 
        FROM SheepGoat	
        WHERE IDFarm = @IDFarm AND 
            (DateBirth <= @DateEnd) AND
            ((IDDispReas = '-') OR
            ((IDDispReas <> '-' AND DateDisp > @DateEnd)))
    	ORDER BY IDSheepGoat
    /*CREATE NONCLUSTERED INDEX IX_SumPerform_SheepGoat ON 
	SumPerform_SheepGoat (IDFarm) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumPerform_SheepGoat_1 ON 
	SumPerform_SheepGoat (IDSheepGoat) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumPerform_SheepGoat_2 ON 
	SumPerform_SheepGoat (BreedCross) ON [PRIMARY]*/
GO
spSelectInto_SumPerform_SheepGoat "¿¿", "01.01.03" -- "01.01.90"
GO
SELECT * FROM SumPerform_SheepGoat
GO
