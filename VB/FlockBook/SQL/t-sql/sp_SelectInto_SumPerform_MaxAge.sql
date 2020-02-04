USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_SumPerform_MaxAge" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_SumPerform_MaxAge
GO
CREATE PROCEDURE spSelectInto_SumPerform_MaxAge @Date smalldatetime/*varchar(8)*/ AS
    DECLARE @DateEnd smalldatetime
    DECLARE @DateBegin smalldatetime
    --SET DATEFORMAT dmy
    SET @DateEnd = /*CAST(*/@Date /*AS smalldatetime)*/
    SET @DateBegin = @DateEnd - 365.25
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumPerform_MaxAge" AND type = "U")
        DROP TABLE SumPerform_MaxAge -- Drop the previous table.
    SELECT IDSheepGoat, MAX(Age) AS MaxAge -- Create a new one.
        INTO SumPerform_MaxAge 
        FROM SumPerform_WeightWoolAnnl
	WHERE (DateAnnl >= @DateBegin AND DateAnnl <= @DateEnd)
	GROUP BY IDSheepGoat
	HAVING (MAX(Age) > 1)
    /*CREATE NONCLUSTERED INDEX IX_SumPerform_MaxAge ON 
	SumPerform_MaxAge (IDSheepGoat) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumPerform_MaxAge_1 ON 
	SumPerform_MaxAge (MaxAge) ON [PRIMARY]*/
GO
spSelectInto_SumPerform_MaxAge "01.01.00" -- "29.01.03" 
GO
SELECT * FROM SumPerform_MaxAge
GO