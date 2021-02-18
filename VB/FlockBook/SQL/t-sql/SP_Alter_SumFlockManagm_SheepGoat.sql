USE FlockBook
GO

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spAlter_SumFlockManagm_SheepGoat" AND type = "P")
DROP PROCEDURE spAlter_SumFlockManagm_SheepGoat
GO

CREATE PROCEDURE spAlter_SumFlockManagm_SheepGoat
AS
ALTER TABLE SumFlockManagm_SheepGoat
ADD IDAgeSex char(1)
/*CREATE NONCLUSTERED INDEX IX_SumFlockManagm_SheepGoat_2 ON 
	SumFlockManagm_SheepGoat (IDAgeSex) ON [PRIMARY]*/
GO

spAlter_SumFlockManagm_SheepGoat
GO
SELECT * FROM SumFlockManagm_SheepGoat
GO
