USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelectInto_SumGenEval_Appraisal" 
    AND type = "P")
    DROP PROCEDURE spSelectInto_SumGenEval_Appraisal
GO
CREATE PROCEDURE spSelectInto_SumGenEval_Appraisal (@DateEnd smalldatetime) AS
    DECLARE @DateBegin smalldatetime
    DECLARE @BVSpan smallint
    EXEC @BVSpan = spSelectInto_SumGenEval_BVSpan --Define the BV calculation span: life time/yrs.
    SET @DateBegin = @DateEnd - CAST(@BVSpan AS smalldatetime) --Define the beginning date.
    IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "SumGenEval_Appraisal" AND type = "U")
	DROP TABLE SumGenEval_Appraisal
    SELECT SumGenEval_FarmBrdSrOffsp.IDFarm, SumGenEval_FarmBrdSrOffsp.BreedCross, 
	SumGenEval_FarmBrdSrOffsp.IDSire, Appraisal.Leng, 
	(Diameter.DiamFrom + Diameter.DiamTo) / 2 AS Diam
	INTO SumGenEval_Appraisal 
	FROM SumGenEval_FarmBrdSrOffsp 
	    INNER JOIN Appraisal ON 
	    	SumGenEval_FarmBrdSrOffsp.IDLambKid = Appraisal.IDSheepGoat 
	    INNER JOIN Diameter ON 
		Appraisal.Diam = Diameter.Diam
	WHERE (Appraisal.DateAppr >= @DateBegin) AND
	    (Appraisal.DateAppr <= @DateEnd) AND 
	    (Appraisal.Age = 1)
    /*CREATE NONCLUSTERED INDEX IX_SumGenEval_Appraisal ON 
	SumGenEval_Appraisal (IDFarm) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumGenEval_Appraisal_1 ON 
	SumGenEval_Appraisal (BreedCross) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumGenEval_Appraisal_2 ON 
	SumGenEval_Appraisal (IDSire) ON [PRIMARY]*/
GO
spSelectInto_SumGenEval_Appraisal "01.23.03" -- "23.01.03"
GO
SELECT * FROM SumGenEval_Appraisal
GO