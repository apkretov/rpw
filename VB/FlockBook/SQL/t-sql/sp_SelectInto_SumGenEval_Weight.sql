USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_SumGenEval_Weight" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_SumGenEval_Weight
GO
CREATE PROCEDURE spSelectInto_SumGenEval_Weight (@DateEnd smalldatetime) AS
    DECLARE @DateBegin smalldatetime
    DECLARE @BVSpan smallint
    EXEC @BVSpan = spSelectInto_SumGenEval_BVSpan --Define the BV calculation span: life time/yrs.
    SET @DateBegin = @DateEnd - CAST(@BVSpan AS smalldatetime) --Define the beginning date.
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumGenEval_Weight" AND type = "U")
	DROP TABLE SumGenEval_Weight
    SELECT SumGenEval_FarmBrdSrOffsp.IDFarm, SumGenEval_FarmBrdSrOffsp.BreedCross, 
	SumGenEval_FarmBrdSrOffsp.IDSire, WeightWoolAnnl.WtAnnl
	INTO SumGenEval_Weight 
	FROM SumGenEval_FarmBrdSrOffsp 
	    INNER JOIN WeightWoolAnnl ON 
		SumGenEval_FarmBrdSrOffsp.IDLambKid = WeightWoolAnnl.IDSheepGoat
	WHERE (WeightWoolAnnl.DateAnnl >= @DateBegin) AND
    	    (WeightWoolAnnl.DateAnnl <= @DateEnd) AND 
	    (WeightWoolAnnl.Age = 1)
    /*CREATE NONCLUSTERED INDEX IX_SumGenEval_Weight ON 
	SumGenEval_Weight (IDFarm) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumGenEval_Weight_1 ON 
	SumGenEval_Weight (BreedCross) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumGenEval_Weight_2 ON 
	SumGenEval_Weight (IDSire) ON [PRIMARY]*/
GO
spSelectInto_SumGenEval_Weight "01.01.02" --"23.01.03"
GO
SELECT * FROM SumGenEval_Weight
GO
