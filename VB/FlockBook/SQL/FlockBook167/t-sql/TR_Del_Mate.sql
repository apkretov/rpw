USE FlockBookRec
GO

IF EXISTS (SELECT name FROM sysobjects 				-- Drop & create the trigger.
WHERE name = "trDel_Mate" AND type = "TR")
DROP TRIGGER trDel_Mate
GO
CREATE TRIGGER trDel_Mate
ON Mate
FOR DELETE
AS 
DELETE LambKid FROM LambKid, deleted				-- Delete LambKid.
WHERE LambKid.IDDam = deleted.IDDam AND
   LambKid.Cycle = deleted.Cycle
GO