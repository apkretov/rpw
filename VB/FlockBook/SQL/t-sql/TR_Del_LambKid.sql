USE FlockBookRec
GO

IF EXISTS (SELECT name FROM sysobjects 				-- Drop & create the trigger.
WHERE name = "trDel_LambKid" AND type = "TR")
DROP TRIGGER trDel_LambKid
GO
CREATE TRIGGER trDel_LambKid
ON LambKid
FOR DELETE
AS 
DELETE Offspring FROM Offspring, deleted			-- Delete Offspring.
WHERE Offspring.IDDam = deleted.IDDam AND
   Offspring.Cycle = deleted.Cycle
GO