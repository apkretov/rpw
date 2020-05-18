USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects 
    WHERE name = "spDelete_Appraisal_IDSheepGoatAge" AND type = "P")
    DROP PROCEDURE spDelete_Appraisal_IDSheepGoatAge
GO
CREATE PROCEDURE spDelete_Appraisal_IDSheepGoatAge (@IDSheepGoat char(6), @Age tinyint) AS
    DELETE Appraisal
	WHERE IDSheepGoat = @IDSheepGoat AND
	Age = @Age
GO
spDelete_Appraisal_IDSheepGoatAge "юб0000", 2
GO
SELECT * FROM Appraisal
GO