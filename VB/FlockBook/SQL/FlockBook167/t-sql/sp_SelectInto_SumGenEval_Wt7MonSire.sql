USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelectInto_SumGenEval_Wt7MonSire" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_SumGenEval_Wt7MonSire
GO
CREATE PROCEDURE spSelectInto_SumGenEval_Wt7MonSire AS
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumGenEval_Wt7MonSire" AND type = "U")
    	DROP TABLE SumGenEval_Wt7MonSire
    SELECT IDFarm, BreedCross, IDSire, AVG(Wt7Mon) AS AvgWt7Mon, COUNT(Wt7Mon) AS CountWt7Mon
	INTO SumGenEval_Wt7MonSire 
	FROM SumGenEval_Wt7Mon
	GROUP BY IDFarm, BreedCross, IDSire
    /*CREATE NONCLUSTERED INDEX IX_SumGenEval_Wt7MonSire ON 
	SumGenEval_Wt7MonSire (IDFarm) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumGenEval_Wt7MonSire_1 ON 
	SumGenEval_Wt7MonSire (BreedCross) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumGenEval_Wt7MonSire_2 ON 
	SumGenEval_Wt7MonSire (IDSire) ON [PRIMARY]*/
GO
spSelectInto_SumGenEval_Wt7MonSire 
GO
SELECT * FROM SumGenEval_Wt7MonSire
GO