USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_SumPerform_WeightWean" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_SumPerform_WeightWean
GO
CREATE PROCEDURE spSelectInto_SumPerform_WeightWean @Date smalldatetime/*varchar(8)*/ AS
    DECLARE @DateEnd smalldatetime
    --SET DATEFORMAT dmy
    SET @DateEnd = /*CAST(*/@Date /*AS smalldatetime)*/
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumPerform_WeightWean" AND type = "U")
        DROP TABLE SumPerform_WeightWean -- Drop the previous table.
    SELECT WeightWean.IDLambKid, WeightWean.WtWean -- Create a new one.
        INTO SumPerform_WeightWean 
        FROM WeightWean INNER JOIN SumPerform_SheepGoat ON 
            WeightWean.IDLambKid = SumPerform_SheepGoat.IDSheepGoat	
        WHERE (WeightWean.DateWean <= @DateEnd)
    /*CREATE NONCLUSTERED INDEX IX_SumPerform_WeightWean ON 
	SumPerform_WeightWean (IDLambKid) ON [PRIMARY]*/
GO
spSelectInto_SumPerform_WeightWean "01.01.03" -- "01.01.90"
GO
SELECT * FROM SumPerform_WeightWean
GO