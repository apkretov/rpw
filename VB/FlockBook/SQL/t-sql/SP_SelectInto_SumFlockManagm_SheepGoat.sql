USE FlockBook
GO

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelectInto_SumFlockManagm_SheepGoat" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_SheepGoat
GO

CREATE PROCEDURE spSelectInto_SumFlockManagm_SheepGoat (@IDFarm char(2), @DateEnd smalldatetime/*varchar(8)*/)
AS
--SET DATEFORMAT dmy
-- Drop the previous table.
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_SheepGoat" AND type = "U")
DROP TABLE SumFlockManagm_SheepGoat
-- Create a new one.
SELECT IDFarm, IDSheepGoat, IDSex, DateBirth INTO SumFlockManagm_SheepGoat 
FROM SheepGoat	
WHERE (IDFarm = @IDFarm) and
	(DateBirth <= /*CAST(*/@DateEnd /*AS smalldatetime)*/)
/*CREATE NONCLUSTERED INDEX IX_SumFlockManagm_SheepGoat ON 
	SumFlockManagm_SheepGoat (IDFarm) ON [PRIMARY]
CREATE NONCLUSTERED INDEX IX_SumFlockManagm_SheepGoat_1 ON 
	SumFlockManagm_SheepGoat (IDSheepGoat) ON [PRIMARY]*/
GO

spSelectInto_SumFlockManagm_SheepGoat "ÀÀ", "05.08.02"
GO
SELECT * FROM SumFlockManagm_SheepGoat
GO

