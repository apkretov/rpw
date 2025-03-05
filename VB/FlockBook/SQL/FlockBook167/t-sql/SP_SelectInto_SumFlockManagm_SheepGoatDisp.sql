USE FlockBook
GO

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelectInto_SumFlockManagm_SheepGoatDisp" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_SheepGoatDisp
GO

CREATE PROCEDURE spSelectInto_SumFlockManagm_SheepGoatDisp (@IDFarm char(2), 
	@DateBegin smalldatetime/*varchar(8)*/, @DateEnd smalldatetime/*varchar(8)*/)
AS
--SET DATEFORMAT dmy
-- Drop the previous table.
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_SheepGoatDisp" AND 
	type = "U")
DROP TABLE SumFlockManagm_SheepGoatDisp
-- Create a new one.
SELECT IDFarm, IDSheepGoat, IDSex, DateBirth, DateDisp, IDDispReas 
	INTO SumFlockManagm_SheepGoatDisp 
FROM SheepGoat	
WHERE (IDFarm = @IDFarm) AND
	(IDDispReas <> "-") AND
	(DateDisp >= /*CAST(*/@DateBegin /*AS smalldatetime)*/) AND 
	(DateDisp <= /*CAST(*/@DateEnd /*AS smalldatetime)*/)
/*CREATE NONCLUSTERED INDEX IX_SumFlockManagm_SheepGoatDisp ON 
	SumFlockManagm_SheepGoatDisp (IDFarm) ON [PRIMARY]
CREATE NONCLUSTERED INDEX IX_SumFlockManagm_SheepGoatDisp_1 ON 
	SumFlockManagm_SheepGoatDisp (IDDispReas) ON [PRIMARY]*/
GO

spSelectInto_SumFlockManagm_SheepGoatDisp "ÀÀ", "01.01.90", "08.08.02"
GO
SELECT * FROM SumFlockManagm_SheepGoatDisp
GO
