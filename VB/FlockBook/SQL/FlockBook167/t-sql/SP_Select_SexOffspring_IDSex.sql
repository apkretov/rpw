USE FlockBookRec
GO

IF EXISTS (SELECT NAME FROM sysobjects 
   WHERE NAME = "spSelect_SexOffspring_IDSex" AND type = "P")
DROP PROCEDURE spSelect_SexOffspring_IDSex
GO

CREATE PROCEDURE spSelect_SexOffspring_IDSex (@IDSex char(1)) 
AS
SELECT * FROM SexOffspring
WHERE IDSex = @IDSex
GO

spSelect_SexOffspring_IDSex "0"
GO