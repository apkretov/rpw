USE FlockBookRec
GO

IF EXISTS (SELECT name FROM sysobjects 
WHERE NAME = "spSelect_Offspring_IDLmK" AND type = "P")
DROP PROCEDURE spSelect_Offspring_IDLmK
GO
CREATE PROCEDURE spSelect_Offspring_IDLmK (@IDLambKid char(6))
AS
SELECT IDLambKid FROM Offspring
WHERE IDLambKid = @IDLambKid
GO 

spSelect_Offspring_IDLmK "¿√0010"
GO