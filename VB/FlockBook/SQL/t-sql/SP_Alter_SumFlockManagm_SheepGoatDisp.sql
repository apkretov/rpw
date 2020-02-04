USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spAlter_SumFlockManagm_SheepGoatDisp" AND type = "P")
DROP PROCEDURE spAlter_SumFlockManagm_SheepGoatDisp
GO
CREATE PROCEDURE spAlter_SumFlockManagm_SheepGoatDisp
AS
ALTER TABLE SumFlockManagm_SheepGoatDisp
ADD IDAgeSex char(1)
/*CREATE NONCLUSTERED INDEX IX_SumFlockManagm_SheepGoatDisp_2 ON 
	SumFlockManagm_SheepGoatDisp (IDAgeSex) ON [PRIMARY]*/
GO
spAlter_SumFlockManagm_SheepGoatDisp
GO
SELECT * FROM SumFlockManagm_SheepGoatDisp
GO
