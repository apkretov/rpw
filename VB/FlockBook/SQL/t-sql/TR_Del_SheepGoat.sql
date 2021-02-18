USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects 				-- Drop & create the trigger.
WHERE name = "trDel_SheepGoat" AND type = "TR")
DROP TRIGGER trDel_SheepGoat
GO
CREATE TRIGGER trDel_SheepGoat
ON SheepGoat
FOR DELETE
AS 
UPDATE SheepGoat						-- Update SheepGoat: IDSire.
SET SheepGoat.IDSire = "-     " FROM SheepGoat, deleted
WHERE SheepGoat.IDSire = deleted.IDSheepGoat 
UPDATE SheepGoat						-- 		   : IDDam.
SET SheepGoat.IDDam = "-     " FROM SheepGoat, deleted
WHERE SheepGoat.IDDam = deleted.IDSheepGoat 

DELETE BreedCross FROM BreedCross, deleted			-- Delete BreedCross.
WHERE BreedCross.IDSheepGoat = deleted.IDSheepGoat

DELETE TransFarm FROM TransFarm, deleted			-- Delete TransFarm.
WHERE TransFarm.IDSheepGoat = deleted.IDSheepGoat

DELETE SelIndxCompClass FROM SelIndxCompClass, deleted		-- Delete SelIndxCompClass.
WHERE SelIndxCompClass.IDSheepGoat = deleted.IDSheepGoat

DELETE TestSire FROM TestSire, deleted				-- Delete TestSire.
WHERE TestSire.IDSire = deleted.IDSheepGoat

DELETE Mate FROM Mate, deleted					-- Delete Mate: IDDam.
WHERE Mate.IDDam = deleted.IDSheepGoat
DELETE Mate FROM Mate, deleted					-- 	      : IDSire.
WHERE Mate.IDSire = deleted.IDSheepGoat

DELETE LambKid FROM LambKid, deleted				-- Delete LambKid.
WHERE LambKid.IDDam = deleted.IDSheepGoat

DELETE Offspring FROM Offspring, deleted			-- Delete Offspring: IDDam.
WHERE Offspring.IDDam = deleted.IDSheepGoat
DELETE Offspring FROM Offspring, deleted			-- 		   : IDLambKid.
WHERE Offspring.IDLambKid = deleted.IDSheepGoat

DELETE WeightWean FROM WeightWean, deleted			-- Delete WeightWean.
WHERE WeightWean.IDLambKid = deleted.IDSheepGoat

DELETE Weight7Mon FROM Weight7Mon, deleted			-- Delete Weight7Mon.
WHERE Weight7Mon.IDLambKid = deleted.IDSheepGoat

DELETE WeightWoolAnnl FROM WeightWoolAnnl, deleted		-- Delete WeightWoolAnnl.
WHERE WeightWoolAnnl.IDSheepGoat = deleted.IDSheepGoat

DELETE Appraisal FROM Appraisal, deleted			-- Delete Appraisal.
WHERE Appraisal.IDSheepGoat = deleted.IDSheepGoat
GO