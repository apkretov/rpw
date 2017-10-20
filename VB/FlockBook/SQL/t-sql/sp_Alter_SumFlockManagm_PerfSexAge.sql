USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spAlter_SumFlockManagm_PerfSexAge" AND type = "P")
DROP PROCEDURE spAlter_SumFlockManagm_PerfSexAge
GO
CREATE PROCEDURE spAlter_SumFlockManagm_PerfSexAge
AS
ALTER TABLE SumFlockManagm_PerfSexAge ADD CONSTRAINT
	PK_SumFlockManagm_PerfSexAge PRIMARY KEY CLUSTERED 
	(
	IDFarm,
	IDAgeSex
	) ON [PRIMARY]
GO
spAlter_SumFlockManagm_PerfSexAge
GO
SELECT * FROM SumFlockManagm_PerfSexAge
GO