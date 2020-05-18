USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_SumPerform_Appraisal" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_SumPerform_Appraisal
GO
CREATE PROCEDURE spSelectInto_SumPerform_Appraisal @Date smalldatetime/*varchar(8)*/ AS
    DECLARE @DateEnd smalldatetime
    --SET DATEFORMAT dmy
    SET @DateEnd = /*CAST(*/@Date /*AS smalldatetime)*/
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumPerform_Appraisal" AND type = "U")
        DROP TABLE SumPerform_Appraisal  -- Drop the previous table.
	SELECT Appraisal.IDSheepGoat, Appraisal.Age, Appraisal.Leng, -- Create a new one.
	    (Diameter.DiamFrom + Diameter.DiamTo) / 2 AS Diam
            INTO SumPerform_Appraisal 						    
	    FROM SumPerform_SheepGoat INNER JOIN Appraisal ON 
		SumPerform_SheepGoat.IDSheepGoat = Appraisal.IDSheepGoat INNER JOIN Diameter ON 
		Appraisal.Diam = Diameter.Diam
            WHERE (Appraisal.DateAppr <= @DateEnd)
    /*CREATE NONCLUSTERED INDEX IX_SumPerform_Appraisal ON 
	SumPerform_Appraisal (Age) ON [PRIMARY]*/
GO
spSelectInto_SumPerform_Appraisal "01.29.03"
GO
SELECT * FROM SumPerform_Appraisal
GO