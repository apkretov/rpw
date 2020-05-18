USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_SumFlockManagm_PerfSexAge_WoolMaxAge" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_SumFlockManagm_PerfSexAge_WoolMaxAge
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_PerfSexAge_WoolMaxAge (@DateBegin smalldatetime/*varchar(8)*/,
    @DateEnd smalldatetime/*varchar(8)*/) AS
    DECLARE @DateBeginConv smalldatetime
    DECLARE @DateBeginCurYr smalldatetime -- Current year's beginning.
    DECLARE @DateEndConv smalldatetime
    --SET DATEFORMAT dmy
    SET @DateBeginConv = /*CAST(*/@DateBegin /*AS smalldatetime)*/
    SET @DateEndConv = /*CAST(*/@DateEnd /*AS smalldatetime)*/
    SET @DateBeginCurYr = @DateEndConv - 365.25
    IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "SumFlockManagm_PerfSexAge_WoolMaxAge" AND type = "U") 
        DROP TABLE SumFlockManagm_PerfSexAge_WoolMaxAge
    SELECT IDSheepGoat, MAX(Age) AS MaxAge -- Create a new one.
        INTO SumFlockManagm_PerfSexAge_WoolMaxAge 
        FROM SumFlockManagm_WoolAnnl
	WHERE (DateShearAnnl >= @DateBeginConv AND 
	    DateShearAnnl >= @DateBeginCurYr AND 
	    DateShearAnnl <= @DateEndConv)
	GROUP BY IDSheepGoat
	HAVING (MAX(Age) > 1)
    /*CREATE NONCLUSTERED INDEX IX_SumFlockManagm_PerfSexAge_WoolMaxAge ON 
	SumFlockManagm_PerfSexAge_WoolMaxAge (IDSheepGoat) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumFlockManagm_PerfSexAge_WoolMaxAge_1 ON 
	SumFlockManagm_PerfSexAge_WoolMaxAge (MaxAge) ON [PRIMARY]*/
GO
spSelectInto_SumFlockManagm_PerfSexAge_WoolMaxAge "01.01.90", "01.31.03" 
GO
SELECT * FROM SumFlockManagm_PerfSexAge_WoolMaxAge
GO