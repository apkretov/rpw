USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects 
    WHERE name = "spSelectInto_SumFlockManagm_Appraisal" AND type = "P")
    DROP PROCEDURE spSelectInto_SumFlockManagm_Appraisal
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_Appraisal (@IDFarm char(2), @DateBegin smalldatetime/*varchar(8)*/, 
    @DateEnd smalldatetime/*varchar(8)*/) AS
    --SET DATEFORMAT dmy
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_Appraisal" AND 
	type = "U")
	DROP TABLE SumFlockManagm_Appraisal -- Drop the previous table.
    SELECT SheepGoat.IDFarm, Appraisal.IDSheepGoat, Appraisal.Age, Appraisal.DateAppr, 
	Appraisal.Leng, (Diameter.DiamFrom + Diameter.DiamTo) / 2 AS Diam -- Create a new one.
	INTO SumFlockManagm_Appraisal
	FROM SheepGoat INNER JOIN Appraisal ON SheepGoat.IDSheepGoat = Appraisal.IDSheepGoat 
	    INNER JOIN Diameter ON Appraisal.Diam = Diameter.Diam
	WHERE (SheepGoat.IDFarm = @IDFarm) AND 
	    (Appraisal.DateAppr >= /*CAST(*/@DateBegin /*AS smalldatetime)*/) AND 
	    (Appraisal.DateAppr <= /*CAST(*/@DateEnd /*AS smalldatetime)*/)
    /*CREATE NONCLUSTERED INDEX IX_SumFlockManagm_Appraisal ON 
	SumFlockManagm_Appraisal (Age) ON [PRIMARY]*/
GO
spSelectInto_SumFlockManagm_Appraisal "ÀÀ", "01.01.90", "05.08.02"
GO
SELECT * FROM SumFlockManagm_Appraisal
GO