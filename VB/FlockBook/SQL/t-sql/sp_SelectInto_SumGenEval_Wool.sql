USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_SumGenEval_Wool" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_SumGenEval_Wool
GO
CREATE PROCEDURE spSelectInto_SumGenEval_Wool (@DateEnd smalldatetime) AS
    DECLARE @DateBegin smalldatetime
    DECLARE @BVSpan smallint
    EXEC @BVSpan = spSelectInto_SumGenEval_BVSpan --Define the BV calculation span: life time/yrs.
    SET @DateBegin = @DateEnd - CAST(@BVSpan AS smalldatetime) --Define the beginning date.
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumGenEval_Wool" AND type = "U")
	DROP TABLE SumGenEval_Wool
    SELECT SumGenEval_FarmBrdSrOffsp.IDFarm, SumGenEval_FarmBrdSrOffsp.BreedCross, 
	SumGenEval_FarmBrdSrOffsp.IDSire, WeightWoolAnnl.GreaseAnnl
	INTO SumGenEval_Wool 
	FROM SumGenEval_FarmBrdSrOffsp 
	    INNER JOIN WeightWoolAnnl ON 
		SumGenEval_FarmBrdSrOffsp.IDLambKid = WeightWoolAnnl.IDSheepGoat
	WHERE (WeightWoolAnnl.DateShearAnnl >= @DateBegin) AND
    	    (WeightWoolAnnl.DateShearAnnl <= @DateEnd) AND 
	    (WeightWoolAnnl.Age = 1)
    /*CREATE NONCLUSTERED INDEX IX_SumGenEval_Wool ON 
	SumGenEval_Wool (IDFarm) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumGenEval_Wool_1 ON 
	SumGenEval_Wool (BreedCross) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumGenEval_Wool_2 ON 
	SumGenEval_Wool (IDSire) ON [PRIMARY]*/
GO
spSelectInto_SumGenEval_Wool "01.01.02" --"23.01.03"
GO
SELECT * FROM SumGenEval_Wool
GO

