USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelectInto_SumGenEval_ApprSire" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_SumGenEval_ApprSire
GO
CREATE PROCEDURE spSelectInto_SumGenEval_ApprSire AS
    SET DATEFORMAT dmy
    IF EXISTS (SELECT * FROM sysobjects WHERE id = object_id(N'SumGenEval_ApprSire') AND 
        OBJECTPROPERTY(id, N'IsUserTable') = 1) -- Drop the previous table.
        DROP TABLE SumGenEval_ApprSire
    SELECT IDFarm, BreedCross, IDSire, AVG(Leng) AS AvgLeng, COUNT(Leng) AS CountLeng, AVG(Diam) AS AvgDiam, 
        COUNT(Diam) AS CountDiam
        INTO SumGenEval_ApprSire 
        FROM SumGenEval_Appraisal
        GROUP BY IDFarm, BreedCross, IDSire
    /*CREATE NONCLUSTERED INDEX IX_SumGenEval_ApprSire ON 
	SumGenEval_ApprSire (IDFarm) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumGenEval_ApprSire_1 ON 
	SumGenEval_ApprSire (BreedCross) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumGenEval_ApprSire_2 ON 
	SumGenEval_ApprSire (IDSire) ON [PRIMARY]*/
GO
spSelectInto_SumGenEval_ApprSire 
GO
SELECT * FROM SumGenEval_ApprSire
GO