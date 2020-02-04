USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_SumGenEval_WoolSire" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_SumGenEval_WoolSire
GO
CREATE PROCEDURE spSelectInto_SumGenEval_WoolSire AS
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumGenEval_WoolSire" AND type = "U")
    	DROP TABLE SumGenEval_WoolSire
    SELECT IDFarm, BreedCross, IDSire, AVG(GreaseAnnl) AS AvgGrease1Yr, COUNT(GreaseAnnl) AS CountGrease1Yr
	INTO SumGenEval_WoolSire 
	FROM SumGenEval_Wool
	GROUP BY IDFarm, BreedCross, IDSire
    /*CREATE NONCLUSTERED INDEX IX_SumGenEval_WoolSire ON 
	SumGenEval_WoolSire (IDFarm) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumGenEval_WoolSire_1 ON 
	SumGenEval_WoolSire (BreedCross) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumGenEval_WoolSire_2 ON 
	SumGenEval_WoolSire (IDSire) ON [PRIMARY]*/
GO
spSelectInto_SumGenEval_WoolSire 
GO
SELECT * FROM SumGenEval_WoolSire
GO