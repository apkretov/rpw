USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects 
    WHERE name = "spSelectInto_SumFlockManagm_PerfSexAge_WtAnnl" AND type = "P")
    DROP PROCEDURE spSelectInto_SumFlockManagm_PerfSexAge_WtAnnl
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_PerfSexAge_WtAnnl @DateEnd smalldatetime/*varchar(8)*/
AS
DECLARE @DateEndConv smalldatetime
DECLARE @DateBegin smalldatetime
--SET DATEFORMAT dmy
SET @DateEndConv = /*CAST(*/@DateEnd /*AS smalldatetime)*/
SET @DateBegin = @DateEndConv - 365.25
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_PerfSexAge_WtAnnl" AND 
    type = "U")
    DROP TABLE SumFlockManagm_PerfSexAge_WtAnnl
SELECT SumFlockManagm_PerfSexAge_WtMaxAge.IDSheepGoat, SumFlockManagm_WeightAnnl.WtAnnl
    INTO SumFlockManagm_PerfSexAge_WtAnnl -- Create a new one.
FROM SumFlockManagm_PerfSexAge_WtMaxAge INNER JOIN SumFlockManagm_WeightAnnl ON 
    SumFlockManagm_PerfSexAge_WtMaxAge.IDSheepGoat = SumFlockManagm_WeightAnnl.IDSheepGoat 
    AND SumFlockManagm_PerfSexAge_WtMaxAge.MaxAge = SumFlockManagm_WeightAnnl.Age
WHERE SumFlockManagm_WeightAnnl.DateAnnl >= @DateBegin AND
    SumFlockManagm_WeightAnnl.DateAnnl <= @DateEndConv 
/*CREATE NONCLUSTERED INDEX IX_SumFlockManagm_PerfSexAge_WtAnnl ON 
    SumFlockManagm_PerfSexAge_WtAnnl (IDSheepGoat) ON [PRIMARY]*/
GO
spSelectInto_SumFlockManagm_PerfSexAge_WtAnnl "01.31.02" -- "31.01.03"
GO
SELECT * FROM SumFlockManagm_PerfSexAge_WtAnnl
GO
