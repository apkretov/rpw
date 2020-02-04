USE FlockBookRec
GO

IF EXISTS (SELECT name FROM sysobjects WHERE 
	NAME = "spDropTable_SumGenEval" AND type = "P")
DROP PROCEDURE spDropTable_SumGenEval
GO

CREATE PROCEDURE spDropTable_SumGenEval
AS
-- Drop the SumGenEval_FarmSireOffspring table.
IF exists (SELECT * FROM sysobjects WHERE id = object_id(N'SumGenEval_FarmSireOffspring') 
	and OBJECTPROPERTY(id, N'IsUserTable') = 1)
DROP TABLE SumGenEval_FarmSireOffspring
GO

spDropTable_SumGenEval
GO