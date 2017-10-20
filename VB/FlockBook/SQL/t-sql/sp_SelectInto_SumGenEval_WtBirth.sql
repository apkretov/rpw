USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_SumGenEval_WtBirth" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_SumGenEval_WtBirth
GO
CREATE PROCEDURE spSelectInto_SumGenEval_WtBirth (@DateEnd smalldatetime) AS
    DECLARE @DateBegin smalldatetime
    DECLARE @BVSpan smallint
    EXEC @BVSpan = spSelectInto_SumGenEval_BVSpan --Define the BV calculation span: life time/yrs.
    SET @DateBegin = @DateEnd - CAST(@BVSpan AS smalldatetime) --Define the beginning date.
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumGenEval_WtBirth" AND type = "U")
    	DROP TABLE SumGenEval_WtBirth
    SELECT SumGenEval_FarmBrdSrOffsp.IDFarm, SumGenEval_FarmBrdSrOffsp.BreedCross, 
	SumGenEval_FarmBrdSrOffsp.IDSire, Offspring.WtBirth 
	INTO SumGenEval_WtBirth 
	FROM SumGenEval_FarmBrdSrOffsp
	    INNER JOIN Offspring ON 
    		SumGenEval_FarmBrdSrOffsp.IDLambKid = Offspring.IDLambKid
     	    INNER JOIN LambKid ON 
    		Offspring.IDDam = LambKid.IDDam AND 
    		Offspring.Cycle = LambKid.Cycle
	WHERE (LambKid.DateLambKid >= @DateBegin) AND
    	    (LambKid.DateLambKid <= @DateEnd)
    /*CREATE NONCLUSTERED INDEX IX_SumGenEval_WtBirth ON 
	SumGenEval_WtBirth (IDFarm) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumGenEval_WtBirth_1 ON 
	SumGenEval_WtBirth (BreedCross) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumGenEval_WtBirth_2 ON 
	SumGenEval_WtBirth (IDSire) ON [PRIMARY]*/
GO
spSelectInto_SumGenEval_WtBirth "01.01.01" --"23.01.03"
GO
SELECT * FROM SumGenEval_WtBirth
GO


