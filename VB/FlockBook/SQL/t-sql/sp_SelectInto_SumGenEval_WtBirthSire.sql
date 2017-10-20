USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelectInto_SumGenEval_WtBirthSire" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_SumGenEval_WtBirthSire
GO
CREATE PROCEDURE spSelectInto_SumGenEval_WtBirthSire AS
    IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "SumGenEval_WtBirthSire" AND type = "U")
    	DROP TABLE SumGenEval_WtBirthSire
    SELECT IDFarm, BreedCross, IDSire, AVG(WtBirth) AS AvgWtBirth, COUNT(WtBirth) AS CountWtBirth
	INTO SumGenEval_WtBirthSire 
	FROM SumGenEval_WtBirth
	GROUP BY IDFarm, BreedCross, IDSire
    /*CREATE NONCLUSTERED INDEX IX_SumGenEval_WtBirthSire ON 
	SumGenEval_WtBirthSire (IDFarm) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumGenEval_WtBirthSire_1 ON 
	SumGenEval_WtBirthSire (BreedCross) ON [PRIMARY]*/
GO
spSelectInto_SumGenEval_WtBirthSire 
GO
SELECT * FROM SumGenEval_WtBirthSire
GO