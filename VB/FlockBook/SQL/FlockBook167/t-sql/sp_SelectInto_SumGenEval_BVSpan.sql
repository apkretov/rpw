USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelectInto_SumGenEval_BVSpan" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_SumGenEval_BVSpan
GO
CREATE PROCEDURE spSelectInto_SumGenEval_BVSpan
AS
DECLARE @YrDays real
DECLARE @Yr smallint
SET DATEFORMAT dmy
SET @YrDays = 365.25
IF (SELECT BVTestLifeTime FROM ContrlParam) = 1 --Define the calculation span: life time/yrs.
    SELECT @Yr = LifeTimeMax FROM ContrlParam
ELSE
    SELECT @Yr = BVTestYr FROM ContrlParam
RETURN @YrDays * @Yr + 0.75 --Add as if rounded.
GO
DECLARE @RetVal int --Test.
EXEC @RetVal = spSelectInto_SumGenEval_BVSpan
PRINT "@RetVal:"
PRINT @RetVal 
GO
