USE FlockBookRec
GO

IF EXISTS (SELECT name FROM sysobjects 		
WHERE name = "spCheck_SheepGoat" AND type = "P")
DROP PROCEDURE spCheck_SheepGoat
GO
CREATE PROCEDURE spCheck_SheepGoat
AS 
ALTER TABLE BreedCross 
CHECK CONSTRAINT FK_BreedCross_SheepGoat		-- Disable the foreign key.
GO

spCheck_SheepGoat
GO