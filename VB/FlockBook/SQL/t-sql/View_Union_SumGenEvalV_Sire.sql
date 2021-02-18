USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumGenEvalV_Union_Sire" AND type = "V") 
    DROP VIEW SumGenEvalV_Union_Sire -- Drop the previous view.
GO
CREATE VIEW SumGenEvalV_Union_Sire
AS
SELECT IDFarm, IDSire
FROM SumGenEval_WtBirthSire
UNION
SELECT IDFarm, IDSire
FROM SumGenEval_WtWeanSire
UNION
SELECT IDFarm, IDSire
FROM SumGenEval_Wt7MonSire
UNION
SELECT IDFarm, IDSire
FROM SumGenEval_WeightWoolSire
GO
SELECT * FROM SumGenEvalV_Union_Sire
GO