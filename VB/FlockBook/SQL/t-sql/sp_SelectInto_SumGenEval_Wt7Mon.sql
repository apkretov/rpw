USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_SumGenEval_Wt7Mon" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_SumGenEval_Wt7Mon
GO
CREATE PROCEDURE spSelectInto_SumGenEval_Wt7Mon (@DateEnd smalldatetime) AS
    DECLARE @DateBegin smalldatetime
    DECLARE @BVSpan smallint
    EXEC @BVSpan = spSelectInto_SumGenEval_BVSpan --Define the BV calculation span: life time/yrs.
    SET @DateBegin = @DateEnd - CAST(@BVSpan AS smalldatetime) --Define the beginning date.
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumGenEval_Wt7Mon" AND type = "U")
	DROP TABLE SumGenEval_Wt7Mon
    SELECT SumGenEval_FarmBrdSrOffsp.IDFarm, SumGenEval_FarmBrdSrOffsp.BreedCross, 
	SumGenEval_FarmBrdSrOffsp.IDSire, Weight7Mon.Wt7Mon 
	INTO SumGenEval_Wt7Mon 
	FROM SumGenEval_FarmBrdSrOffsp 
	    INNER JOIN Weight7Mon ON 
    		SumGenEval_FarmBrdSrOffsp.IDLambKid = Weight7Mon.IDLambKid
	WHERE (Weight7Mon.Date7Mon >= @DateBegin) AND
    	    (Weight7Mon.Date7Mon <= @DateEnd)
    /*CREATE NONCLUSTERED INDEX IX_SumGenEval_Wt7Mon ON 
	SumGenEval_Wt7Mon (IDFarm) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumGenEval_Wt7Mon_1 ON 
	SumGenEval_Wt7Mon (BreedCross) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumGenEval_Wt7Mon_2 ON 
	SumGenEval_Wt7Mon (IDSire) ON [PRIMARY]*/
GO
spSelectInto_SumGenEval_Wt7Mon "01.01.01" --"23.01.03"
GO
SELECT * FROM SumGenEval_Wt7Mon
GO

