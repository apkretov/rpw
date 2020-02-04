USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelectInto_SumFlockManagm_WoolAnnl" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_WoolAnnl
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_WoolAnnl (@IDFarm char(2), @DateBegin smalldatetime/*varchar(8)*/, 
	@DateEnd smalldatetime/*varchar(8)*/)
AS
--SET DATEFORMAT dmy
-- Drop the previous table.
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_WoolAnnl" AND type = "U")
DROP TABLE SumFlockManagm_WoolAnnl
-- Create a new one.
SELECT SheepGoat.IDFarm, WeightWoolAnnl.IDSheepGoat, WeightWoolAnnl.Age, 
	WeightWoolAnnl.DateShearAnnl, WeightWoolAnnl.GreaseAnnl/*, SheepGoat.IDSex*/, 
	SheepGoat.DateBirth INTO SumFlockManagm_WoolAnnl
FROM SheepGoat INNER JOIN WeightWoolAnnl ON SheepGoat.IDSheepGoat = WeightWoolAnnl.IDSheepGoat
WHERE (SheepGoat.IDFarm = @IDFarm) AND 
	(WeightWoolAnnl.DateShearAnnl >= /*CAST(*/@DateBegin /*AS smalldatetime)*/) AND 
	(WeightWoolAnnl.DateShearAnnl <= /*CAST(*/@DateEnd /*AS smalldatetime)*/)
    /*CREATE NONCLUSTERED INDEX IX_SumFlockManagm_WoolAnnl ON 
	SumFlockManagm_WoolAnnl (Age) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumFlockManagm_WoolAnnl_1 ON 
	SumFlockManagm_WoolAnnl (IDSheepGoat) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumFlockManagm_WoolAnnl_2 ON 
	SumFlockManagm_WoolAnnl (DateShearAnnl) ON [PRIMARY]*/
GO
spSelectInto_SumFlockManagm_WoolAnnl "ÀÀ", "01.01.90", "05.08.02"
go
select * from SumFlockManagm_WoolAnnl
go
