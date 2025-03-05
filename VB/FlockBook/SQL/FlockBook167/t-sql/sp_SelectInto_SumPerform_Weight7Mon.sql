USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_SumPerform_Weight7Mon" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_SumPerform_Weight7Mon
GO
CREATE PROCEDURE spSelectInto_SumPerform_Weight7Mon @Date smalldatetime/*varchar(8)*/ AS
    DECLARE @DateEnd smalldatetime
    --SET DATEFORMAT dmy
    SET @DateEnd = /*CAST(*/@Date /*AS smalldatetime)*/
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumPerform_Weight7Mon" AND type = "U")
        DROP TABLE SumPerform_Weight7Mon  -- Drop the previous table.
    SELECT Weight7Mon.IDLambKid, Weight7Mon.Wt7Mon -- Create a new one.
        INTO SumPerform_Weight7Mon 
        FROM Weight7Mon INNER JOIN SumPerform_SheepGoat ON 
            Weight7Mon.IDLambKid = SumPerform_SheepGoat.IDSheepGoat	
        WHERE (Weight7Mon.Date7Mon <= @DateEnd)
    /*CREATE NONCLUSTERED INDEX IX_SumPerform_Weight7Mon ON 
	SumPerform_Weight7Mon (IDLambKid) ON [PRIMARY]*/
GO
spSelectInto_SumPerform_Weight7Mon "01.29.03" -- "01.01.90"
GO
SELECT * FROM SumPerform_Weight7Mon
GO

