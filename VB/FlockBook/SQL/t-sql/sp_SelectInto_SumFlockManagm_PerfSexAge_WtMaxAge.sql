USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_SumFlockManagm_PerfSexAge_WtMaxAge" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_SumFlockManagm_PerfSexAge_WtMaxAge
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_PerfSexAge_WtMaxAge (@DateBegin smalldatetime/*varchar(8)*/,
    @DateEnd smalldatetime/*varchar(8)*/) AS
    DECLARE @DateBeginConv smalldatetime
    DECLARE @DateBeginCurYr smalldatetime -- Current year's beginning.
    DECLARE @DateEndConv smalldatetime
    --SET DATEFORMAT dmy
    SET @DateBeginConv = /*CAST(*/@DateBegin /*AS smalldatetime)*/
    SET @DateEndConv = /*CAST(*/@DateEnd /*AS smalldatetime)*/
    SET @DateBeginCurYr = @DateEndConv - 365.25
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_PerfSexAge_WtMaxAge" AND 
    	type = "U") 
        DROP TABLE SumFlockManagm_PerfSexAge_WtMaxAge
    SELECT IDSheepGoat, MAX(Age) AS MaxAge -- Create a new one.
        INTO SumFlockManagm_PerfSexAge_WtMaxAge 
        FROM SumFlockManagm_WeightAnnl
	WHERE (DateAnnl >= @DateBeginConv AND 
	    DateAnnl >= @DateBeginCurYr AND 
	    DateAnnl <= @DateEndConv)
	GROUP BY IDSheepGoat
	HAVING (MAX(Age) > 1)
    /*CREATE NONCLUSTERED INDEX IX_SumFlockManagm_PerfSexAge_WtMaxAge ON 
	SumFlockManagm_PerfSexAge_WtMaxAge (IDSheepGoat) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumFlockManagm_PerfSexAge_WtMaxAge_1 ON 
	SumFlockManagm_PerfSexAge_WtMaxAge (MaxAge) ON [PRIMARY]*/
GO
spSelectInto_SumFlockManagm_PerfSexAge_WtMaxAge "01.01.90", "01.31.03" 
GO
SELECT * FROM SumFlockManagm_PerfSexAge_WtMaxAge
GO
