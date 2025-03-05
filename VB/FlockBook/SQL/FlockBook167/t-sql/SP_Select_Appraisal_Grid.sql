USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_Appraisal_Grid" AND type = "P")
    DROP PROCEDURE spSelect_Appraisal_Grid
GO
CREATE PROCEDURE spSelect_Appraisal_Grid (@Defect varchar(50)) AS
SELECT Appraisal.IDSheepGoat AS Номер, Appraisal.Age AS Цикл, Appraisal.DateAppr AS Дата
    FROM Defects 
	INNER JOIN InhertDefect ON 
    	    Defects.IDDefect = InhertDefect.IDDefect 
	INNER JOIN Appraisal ON 
    	    InhertDefect.IDSheepGoat = Appraisal.IDSheepGoat AND
     	    InhertDefect.Age = Appraisal.Age
WHERE Defects.Defect = @Defect
GO
spSelect_Appraisal_Grid "Рога, роговые наросты, шишки"
GO
