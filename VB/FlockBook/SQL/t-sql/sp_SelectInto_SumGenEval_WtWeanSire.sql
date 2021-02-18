USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_SumGenEval_WtWeanSire" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_SumGenEval_WtWeanSire
GO
CREATE PROCEDURE spSelectInto_SumGenEval_WtWeanSire AS
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumGenEval_WtWeanSire" AND type = "U") 
    	DROP TABLE SumGenEval_WtWeanSire
    SELECT IDFarm, BreedCross, IDSire, AVG(WtWean) AS AvgWtWean, COUNT(WtWean) AS CountWtWean
	INTO SumGenEval_WtWeanSire 
	FROM SumGenEval_WtWean
	GROUP BY IDFarm, BreedCross, IDSire
    /*CREATE NONCLUSTERED INDEX IX_SumGenEval_WtWeanSire ON 
	SumGenEval_WtWeanSire (IDFarm) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumGenEval_WtWeanSire_1 ON 
	SumGenEval_WtWeanSire (BreedCross) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumGenEval_WtWeanSire_2 ON 
	SumGenEval_WtWeanSire (IDSire) ON [PRIMARY]*/
GO
spSelectInto_SumGenEval_WtWeanSire 
GO
SELECT * FROM SumGenEval_WtWeanSire
GO