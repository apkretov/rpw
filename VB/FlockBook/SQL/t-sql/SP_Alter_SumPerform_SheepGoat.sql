USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spAlter_SumPerform_SheepGoat" AND 
    type = "P")
DROP PROCEDURE spAlter_SumPerform_SheepGoat
GO
CREATE PROCEDURE spAlter_SumPerform_SheepGoat AS
    ALTER TABLE SumPerform_SheepGoat
	ADD IDAgeSex char(1)

    /*CREATE NONCLUSTERED INDEX IX_SumPerform_SheepGoat_3 ON 
	SumPerform_SheepGoat (IDAgeSex) ON [PRIMARY]*/
GO
spSelectInto_SumPerform_SheepGoat "¿¿", "01.01.03"
GO
spAlter_SumPerform_SheepGoat
GO
SELECT * FROM SumPerform_SheepGoat
GO
