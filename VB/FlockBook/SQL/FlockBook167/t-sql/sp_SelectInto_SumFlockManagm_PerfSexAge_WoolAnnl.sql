USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects 
    WHERE name = "spSelectInto_SumFlockManagm_PerfSexAge_WoolAnnl" AND type = "P")
    DROP PROCEDURE spSelectInto_SumFlockManagm_PerfSexAge_WoolAnnl
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_PerfSexAge_WoolAnnl @DateEnd smalldatetime/*varchar(8)*/
AS
DECLARE @DateEndConv smalldatetime
DECLARE @DateBegin smalldatetime
--SET DATEFORMAT dmy
SET @DateEndConv = /*CAST(*/@DateEnd /*AS smalldatetime)*/
SET @DateBegin = @DateEndConv - 365.25
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_PerfSexAge_WoolAnnl" AND 
    type = "U")
    DROP TABLE SumFlockManagm_PerfSexAge_WoolAnnl
SELECT SumFlockManagm_PerfSexAge_WoolMaxAge.IDSheepGoat, SumFlockManagm_WoolAnnl.GreaseAnnl -- Create a new one.
INTO SumFlockManagm_PerfSexAge_WoolAnnl
FROM SumFlockManagm_PerfSexAge_WoolMaxAge INNER JOIN SumFlockManagm_WoolAnnl ON 
    SumFlockManagm_PerfSexAge_WoolMaxAge.IDSheepGoat = SumFlockManagm_WoolAnnl.IDSheepGoat AND 
    SumFlockManagm_PerfSexAge_WoolMaxAge.MaxAge = SumFlockManagm_WoolAnnl.Age
WHERE SumFlockManagm_WoolAnnl.DateShearAnnl >= @DateBegin AND
    SumFlockManagm_WoolAnnl.DateShearAnnl <= @DateEndConv 
/*CREATE NONCLUSTERED INDEX IX_SumFlockManagm_PerfSexAge_WoolAnnl ON 
    SumFlockManagm_PerfSexAge_WoolAnnl (IDSheepGoat) ON [PRIMARY]*/
GO
spSelectInto_SumFlockManagm_PerfSexAge_WoolAnnl "01.27.03"
GO
SELECT * FROM SumFlockManagm_PerfSexAge_WoolAnnl
GO