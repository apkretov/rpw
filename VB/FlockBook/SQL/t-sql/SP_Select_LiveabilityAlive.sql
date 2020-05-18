USE FlockBookRec
GO

IF EXISTS (SELECT name FROM sysobjects WHERE 
	NAME = "spSelect_LiveabilityAlive" AND type = "P")
DROP PROCEDURE spSelect_LiveabilityAlive
GO

CREATE PROCEDURE spSelect_LiveabilityAlive AS
SELECT * FROM Liveability
WHERE IDLiv = "0"
GO

spSelect_LiveabilityAlive 
GO