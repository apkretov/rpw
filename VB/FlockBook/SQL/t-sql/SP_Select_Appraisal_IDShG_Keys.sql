USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects 
    WHERE name = "spSelect_Appraisal_IDShG_Keys" AND type = "P")
    DROP PROCEDURE spSelect_Appraisal_IDShG_Keys
GO
CREATE PROCEDURE spSelect_Appraisal_IDShG_Keys (@IDSheepGoat char(6)) AS
    SELECT IDSheepGoat, Age 
	FROM Appraisal
	WHERE IDSheepGoat = @IDSheepGoat
GO
spSelect_Appraisal_IDShG_Keys "¿¿0000"
GO