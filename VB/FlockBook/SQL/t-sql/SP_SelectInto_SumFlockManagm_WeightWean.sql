USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects 
    WHERE name = "spSelectInto_SumFlockManagm_WeightWean" AND type = "P")
    DROP PROCEDURE spSelectInto_SumFlockManagm_WeightWean
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_WeightWean (@IDFarm char(2), @DateBegin smalldatetime/*varchar(8)*/, 
    @DateEnd smalldatetime/*varchar(8)*/)
AS
--SET DATEFORMAT dmy
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_WeightWean" AND type = "U")
    DROP TABLE SumFlockManagm_WeightWean
SELECT /*SheepGoat.IDFarm,*/ WeightWean.IDLambKid, WeightWean.WtWean -- Create a new one.
INTO SumFlockManagm_WeightWean 
FROM SheepGoat INNER JOIN WeightWean ON SheepGoat.IDSheepGoat = WeightWean.IDLambKid
WHERE (SheepGoat.IDFarm = @IDFarm) AND 
    (WeightWean.DateWean >= /*CAST(*/@DateBegin /*AS smalldatetime)*/) AND 
    (WeightWean.DateWean <= /*CAST(*/@DateEnd /*AS smalldatetime)*/)
/*CREATE NONCLUSTERED INDEX IX_SumFlockManagm_WeightWean ON 
	SumFlockManagm_WeightWean (IDLambKid) ON [PRIMARY]*/
GO
spSelectInto_SumFlockManagm_WeightWean "ÀÀ", "01.26.03", "01.27.03"
GO
SELECT * FROM SumFlockManagm_WeightWean
GO