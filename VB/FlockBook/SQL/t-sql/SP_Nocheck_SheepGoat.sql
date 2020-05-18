USE FlockBookRec
GO

IF EXISTS (SELECT name FROM sysobjects 		
WHERE name = "spNocheck_SheepGoat" AND type = "P")
DROP PROCEDURE spNocheck_SheepGoat
GO
CREATE PROCEDURE spNocheck_SheepGoat
AS 
ALTER TABLE BreedCross 
NOCHECK CONSTRAINT FK_BreedCross_SheepGoat		-- Disable the foreign key.
GO

spNocheck_SheepGoat
GO