USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_SumGenEval_WtWean" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_SumGenEval_WtWean
GO
CREATE PROCEDURE spSelectInto_SumGenEval_WtWean (@DateEnd smalldatetime) AS
    DECLARE @DateBegin smalldatetime
    DECLARE @BVSpan smallint
    EXEC @BVSpan = spSelectInto_SumGenEval_BVSpan --Define the BV calculation span: life time/yrs.
    SET @DateBegin = @DateEnd - CAST(@BVSpan AS smalldatetime) --Define the beginning date.
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumGenEval_WtWean" AND type = "U")
	DROP TABLE SumGenEval_WtWean
    SELECT SumGenEval_FarmBrdSrOffsp.IDFarm, SumGenEval_FarmBrdSrOffsp.BreedCross, 
	SumGenEval_FarmBrdSrOffsp.IDSire, WeightWean.WtWean
	INTO SumGenEval_WtWean 
	FROM SumGenEval_FarmBrdSrOffsp 
	    INNER JOIN WeightWean ON 
    		SumGenEval_FarmBrdSrOffsp.IDLambKid = WeightWean.IDLambKid
	WHERE (WeightWean.DateWean >= @DateBegin) AND
    	    (WeightWean.DateWean <= @DateEnd)
    /*CREATE NONCLUSTERED INDEX IX_SumGenEval_WtWean ON 
	SumGenEval_WtWean (IDFarm) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumGenEval_WtWean_1 ON 
	SumGenEval_WtWean (BreedCross) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumGenEval_WtWean_2 ON 
	SumGenEval_WtWean (IDSire) ON [PRIMARY]*/
GO
spSelectInto_SumGenEval_WtWean "01.01.01" --"23.01.03"
GO
SELECT * FROM SumGenEval_WtWean
GO