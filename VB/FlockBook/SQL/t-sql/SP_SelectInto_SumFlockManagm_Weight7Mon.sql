USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelectInto_SumFlockManagm_Weight7Mon" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_Weight7Mon
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_Weight7Mon (@IDFarm char(2), @DateBegin smalldatetime/*varchar(8)*/, 
	@DateEnd smalldatetime/*varchar(8)*/)
AS
--SET DATEFORMAT dmy
-- Drop the previous table.
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_Weight7Mon" AND type = "U")
DROP TABLE SumFlockManagm_Weight7Mon
-- Create a new one.
SELECT /*SheepGoat.IDFarm,*/ Weight7Mon.IDLambKid, Weight7Mon.Wt7Mon 
	INTO SumFlockManagm_Weight7Mon 
FROM SheepGoat INNER JOIN Weight7Mon ON SheepGoat.IDSheepGoat = Weight7Mon.IDLambKid
WHERE (SheepGoat.IDFarm = @IDFarm) AND 
	(Weight7Mon.Date7Mon >= /*CAST(*/@DateBegin /*AS smalldatetime)*/) AND 
	(Weight7Mon.Date7Mon <= /*CAST(*/@DateEnd /*AS smalldatetime)*/)
/*CREATE NONCLUSTERED INDEX IX_SumFlockManagm_Weight7Mon ON 
	SumFlockManagm_Weight7Mon (IDLambKid) ON [PRIMARY]*/
GO
spSelectInto_SumFlockManagm_Weight7Mon "ÀÀ", "01.01.90", "05.08.02"
GO
SELECT * FROM SumFlockManagm_Weight7Mon
GO
