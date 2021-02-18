USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelectInto_SumFlockManagm_LambKidWeaned" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_LambKidWeaned
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_LambKidWeaned (@IDFarm char(2), 
	@DateBegin smalldatetime/*varchar(8)*/, @DateEnd smalldatetime/*varchar(8)*/) 
AS
DECLARE @AgeWeanMax smallint, @DateBeginShift smalldatetime, @DateEndShift smalldatetime 
--SET DATEFORMAT dmy
SET @AgeWeanMax = (SELECT AgeWeanMax FROM ContrlParam)
SET @DateBeginShift = /*CAST(*/@DateBegin /*AS smalldatetime)*/ - @AgeWeanMax
SET @DateEndShift = /*CAST(*/@DateEnd /*AS smalldatetime)*/ - @AgeWeanMax
-- Drop the previous table.
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_LambKidWeaned" AND 
	type = "U")
DROP TABLE SumFlockManagm_LambKidWeaned
-- Create a new one.
SELECT SheepGoat.IDFarm, LambKid.IDDam, LambKid.Cycle, LambKid.CycleLambKid
	INTO SumFlockManagm_LambKidWeaned 
FROM SheepGoat INNER JOIN LambKid ON SheepGoat.IDSheepGoat = LambKid.IDDam
WHERE (SheepGoat.IDFarm = @IDFarm) AND 
	(LambKid.DateLambKid >= @DateBeginShift) AND 
	(LambKid.DateLambKid <= @DateEndShift)
GO

--SET DATEFORMAT dmy
go
spSelectInto_SumFlockManagm_LambKidWeaned "ÀÀ", "01.01.00", "05.08.02"
go
select * from SumFlockManagm_LambKidWeaned
go