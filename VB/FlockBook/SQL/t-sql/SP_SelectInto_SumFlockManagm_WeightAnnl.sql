use FlockBook
go
IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelectInto_SumFlockManagm_WeightAnnl" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_WeightAnnl
GO

CREATE PROCEDURE spSelectInto_SumFlockManagm_WeightAnnl (@IDFarm char(2), @DateBegin smalldatetime/*varchar(8)*/, 
	@DateEnd smalldatetime/*varchar(8)*/)
AS
--SET DATEFORMAT dmy
-- Drop the previous table.
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_WeightAnnl" AND type = "U")
DROP TABLE SumFlockManagm_WeightAnnl
-- Create a new one.
SELECT SheepGoat.IDFarm, WeightWoolAnnl.IDSheepGoat, WeightWoolAnnl.Age, WeightWoolAnnl.DateAnnl,
	WeightWoolAnnl.WtAnnl, SheepGoat.DateBirth 
	INTO SumFlockManagm_WeightAnnl
FROM SheepGoat INNER JOIN WeightWoolAnnl ON SheepGoat.IDSheepGoat = WeightWoolAnnl.IDSheepGoat
WHERE (SheepGoat.IDFarm = @IDFarm) AND 
	(WeightWoolAnnl.DateAnnl >= /*CAST(*/@DateBegin /*AS smalldatetime)*/) AND 
	(WeightWoolAnnl.DateAnnl <= /*CAST(*/@DateEnd /*AS smalldatetime)*/)
/*CREATE NONCLUSTERED INDEX IX_SumFlockManagm_WeightAnnl ON 
	SumFlockManagm_WeightAnnl (IDSheepGoat) ON [PRIMARY]
CREATE NONCLUSTERED INDEX IX_SumFlockManagm_WeightAnnl_1 ON 
	SumFlockManagm_WeightAnnl (Age) ON [PRIMARY]
CREATE NONCLUSTERED INDEX IX_SumFlockManagm_WeightAnnl_2 ON 
	SumFlockManagm_WeightAnnl (DateAnnl) ON [PRIMARY]*/
GO

spSelectInto_SumFlockManagm_WeightAnnl "ÀÀ", "01.01.90", "05.08.02"
go
select * from SumFlockManagm_WeightAnnl
go

