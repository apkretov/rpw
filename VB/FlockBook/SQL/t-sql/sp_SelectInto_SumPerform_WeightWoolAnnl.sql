USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_SumPerform_WeightWoolAnnl" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_SumPerform_WeightWoolAnnl
GO
CREATE PROCEDURE spSelectInto_SumPerform_WeightWoolAnnl @Date smalldatetime/*varchar(8)*/ AS
    DECLARE @DateEnd smalldatetime
    --SET DATEFORMAT dmy
    SET @DateEnd = /*CAST(*/@Date /*AS smalldatetime)*/
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumPerform_WeightWoolAnnl" AND 
	type = "U") -- Drop the previous table.
        DROP TABLE SumPerform_WeightWoolAnnl
    SELECT WeightWoolAnnl.IDSheepGoat, WeightWoolAnnl.Age, WeightWoolAnnl.DateAnnl, -- Create a 
	WeightWoolAnnl.WtAnnl, WeightWoolAnnl.GreaseAnnl/*, WeightWoolAnnl.Leng, 	    -- new one.
	WeightWoolAnnl.Diam*/ 
        INTO SumPerform_WeightWoolAnnl 
        FROM SumPerform_SheepGoat INNER JOIN WeightWoolAnnl ON 
            SumPerform_SheepGoat.IDSheepGoat = WeightWoolAnnl.IDSheepGoat	
        WHERE (WeightWoolAnnl.DateAnnl <= @DateEnd)
    /*CREATE NONCLUSTERED INDEX IX_SumPerform_WeightWoolAnnl ON 
	SumPerform_WeightWoolAnnl (Age) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumPerform_WeightWoolAnnl_1 ON 
	SumPerform_WeightWoolAnnl (IDSheepGoat) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumPerform_WeightWoolAnnl_2 ON 
	SumPerform_WeightWoolAnnl (DateAnnl) ON [PRIMARY]*/
GO
spSelectInto_SumPerform_WeightWoolAnnl "01.29.03" -- "01.01.90"
GO
SELECT * FROM SumPerform_WeightWoolAnnl
GO