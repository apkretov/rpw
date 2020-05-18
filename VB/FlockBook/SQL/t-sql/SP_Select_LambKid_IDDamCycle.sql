USE FlockBook
GO

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelect_LambKid_IDDamCycle" AND type = "P")
DROP PROCEDURE spSelect_LambKid_IDDamCycle
GO

CREATE PROCEDURE spSelect_LambKid_IDDamCycle (@IDDam char(6), @Cycle tinyint)
AS
SELECT * FROM LambKid
WHERE IDDam = @IDDam and Cycle = @Cycle
GO