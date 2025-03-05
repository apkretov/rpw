USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelectInto_SumFlockManagm_Mate" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_Mate
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_Mate (@IDFarm char(2), @DateBegin smalldatetime/*varchar(8)*/,
	@DateEnd smalldatetime/*varchar(8)*/)
AS
DECLARE @PregnLengNorm smallint, @DateBeginShift smalldatetime, @DateEndShift smalldatetime 
--SET DATEFORMAT dmy
SET @PregnLengNorm = (SELECT PregnLengNorm FROM ContrlParam) 
SET @DateBeginShift = /*CAST(*/@DateBegin /*AS smalldatetime)*/ - @PregnLengNorm
SET @DateEndShift = /*CAST(*/@DateEnd /*AS smalldatetime)*/ - @PregnLengNorm
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_Mate" AND type = "U") 
DROP TABLE SumFlockManagm_Mate -- Drop the previous table.
SELECT SheepGoat.IDFarm, Mate.IDDam, Mate.Cycle -- Create a new one.
	INTO SumFlockManagm_Mate 
FROM SheepGoat INNER JOIN Mate ON SheepGoat.IDSheepGoat = Mate.IDDam
WHERE (SheepGoat.IDFarm = @IDFarm) AND 
	(SheepGoat.IDDispReas = "- ") AND 
	(Mate.DateMatFrom >= @DateBeginShift) AND 
	(Mate.DateMatFrom <= @DateEndShift)
    /*CREATE NONCLUSTERED INDEX IX_SumFlockManagm_Mate ON 
	SumFlockManagm_Mate (IDFarm) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumFlockManagm_Mate_1 ON 
	SumFlockManagm_Mate (IDDam) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumFlockManagm_Mate_2 ON 
	SumFlockManagm_Mate (Cycle) ON [PRIMARY]*/
GO

--SET DATEFORMAT dmy
GO
spSelectInto_SumFlockManagm_Mate "ÀÀ", "01.01.00", "05.08.02"
GO
select * from SumFlockManagm_Mate
GO