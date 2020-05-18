USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_SumGenEval_WeightSire" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_SumGenEval_WeightSire
GO
CREATE PROCEDURE spSelectInto_SumGenEval_WeightSire AS
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumGenEval_WeightSire" AND type = "U")
    	DROP TABLE SumGenEval_WeightSire
    SELECT IDFarm, BreedCross, IDSire, AVG(WtAnnl) AS AvgWt1Yr, COUNT(WtAnnl) AS CountWt1Yr
	INTO SumGenEval_WeightSire 
	FROM SumGenEval_Weight
	GROUP BY IDFarm, BreedCross, IDSire
    /*CREATE NONCLUSTERED INDEX IX_SumGenEval_WeightSire ON 
	SumGenEval_WeightSire (IDFarm) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumGenEval_WeightSire_1 ON 
	SumGenEval_WeightSire (BreedCross) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumGenEval_WeightSire_2 ON 
	SumGenEval_WeightSire (IDSire) ON [PRIMARY]*/
GO
spSelectInto_SumGenEval_WeightSire 
GO
SELECT * FROM SumGenEval_WeightSire
GO