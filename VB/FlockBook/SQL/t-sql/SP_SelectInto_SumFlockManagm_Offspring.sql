USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelectInto_SumFlockManagm_Offspring" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_Offspring
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_Offspring AS
--SET DATEFORMAT dmy
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_Offspring" AND type = "U")
    DROP TABLE SumFlockManagm_Offspring -- Drop the previous table.
SELECT SumFlockManagm_LambKid.IDFarm, Offspring.IDLambKid -- Create a new one.
INTO SumFlockManagm_Offspring 
FROM SumFlockManagm_LambKid INNER JOIN Offspring ON 
    SumFlockManagm_LambKid.IDDam = Offspring.IDDam AND 
    SumFlockManagm_LambKid.Cycle = Offspring.Cycle
    /*CREATE NONCLUSTERED INDEX IX_SumFlockManagm_Offspring ON 
	SumFlockManagm_Offspring (IDLambKid) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumFlockManagm_Offspring_1 ON 
	SumFlockManagm_Offspring (IDFarm) ON [PRIMARY]*/
GO
spSelectInto_SumFlockManagm_Offspring
GO
SELECT * FROM SumFlockManagm_Offspring
GO