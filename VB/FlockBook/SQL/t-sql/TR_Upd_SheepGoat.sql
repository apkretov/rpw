USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects 					-- Drop & create trigger.
WHERE name = "trUpd_SheepGoat" AND type = "TR")
DROP TRIGGER trUpd_SheepGoat
GO
CREATE TRIGGER trUpd_SheepGoat
ON SheepGoat
FOR UPDATE
AS 
IF UPDATE (IDSheepGoat)						-- Update on changing IDSheepGoat
BEGIN
   UPDATE SheepGoat						-- Update SheepGoat: IDSire.
   SET SheepGoat.IDSire = inserted.IDSheepGoat FROM inserted, deleted
   WHERE SheepGoat.IDSire = deleted.IDSheepGoat 
   UPDATE SheepGoat						-- 		   : IDDam.
   SET SheepGoat.IDDam = inserted.IDSheepGoat FROM inserted, deleted
   WHERE SheepGoat.IDDam = deleted.IDSheepGoat 

   UPDATE BreedCross						-- Update BreedCross.
   SET BreedCross.IDSheepGoat = inserted.IDSheepGoat FROM inserted, deleted
   WHERE BreedCross.IDSheepGoat = deleted.IDSheepGoat 

   UPDATE TransFarm						-- Update TransFarm.
   SET TransFarm.IDSheepGoat = inserted.IDSheepGoat FROM inserted, deleted
   WHERE TransFarm.IDSheepGoat = deleted.IDSheepGoat 

   UPDATE SelIndxCompClass					-- Update SelIndxCompClass.
   SET SelIndxCompClass.IDSheepGoat = inserted.IDSheepGoat FROM inserted, deleted
   WHERE SelIndxCompClass.IDSheepGoat = deleted.IDSheepGoat 

   UPDATE TestSire					-- Update TestSire.
   SET TestSire.IDSire = inserted.IDSheepGoat FROM inserted, deleted
   WHERE TestSire.IDSire = deleted.IDSheepGoat 

   UPDATE Mate							-- Update Mate: IDDam.
   SET Mate.IDDam = inserted.IDSheepGoat FROM inserted, deleted
   WHERE Mate.IDDam = deleted.IDSheepGoat 
   UPDATE Mate							-- 	      : IDSire.
   SET Mate.IDSire = inserted.IDSheepGoat FROM inserted, deleted
   WHERE Mate.IDSire = deleted.IDSheepGoat 

   UPDATE LambKid						-- Update LambKid.
   SET LambKid.IDDam = inserted.IDSheepGoat FROM inserted, deleted
   WHERE LambKid.IDDam = deleted.IDSheepGoat 

   UPDATE Offspring						-- Update Offspring: IDDam.
   SET Offspring.IDDam = inserted.IDSheepGoat FROM inserted, deleted
   WHERE Offspring.IDDam = deleted.IDSheepGoat 
   UPDATE Offspring						-- 		   : IDLambKid.
   SET Offspring.IDLambKid = inserted.IDSheepGoat FROM inserted, deleted
   WHERE Offspring.IDLambKid = deleted.IDSheepGoat

   UPDATE WeightWean						-- Update WeightWean.
   SET WeightWean.IDLambKid = inserted.IDSheepGoat FROM inserted, deleted
   WHERE WeightWean.IDLambKid = deleted.IDSheepGoat 

   UPDATE Weight7Mon						-- Update Weight7Mon.
   SET Weight7Mon.IDLambKid = inserted.IDSheepGoat FROM inserted, deleted
   WHERE Weight7Mon.IDLambKid = deleted.IDSheepGoat 

   UPDATE WeightWoolAnnl					-- Update WeightWoolAnnl.
   SET WeightWoolAnnl.IDSheepGoat = inserted.IDSheepGoat FROM inserted, deleted
   WHERE WeightWoolAnnl.IDSheepGoat = deleted.IDSheepGoat 

   UPDATE Appraisal						-- Update Appraisal.
   SET Appraisal.IDSheepGoat = inserted.IDSheepGoat FROM inserted, deleted
   WHERE Appraisal.IDSheepGoat = deleted.IDSheepGoat 

   UPDATE InhertDefect						-- Update InhertDefect.
   SET InhertDefect.IDSheepGoat = inserted.IDSheepGoat FROM inserted, deleted
   WHERE InhertDefect.IDSheepGoat = deleted.IDSheepGoat 
END
IF UPDATE (IDSex)						-- Update on changing IDSex
BEGIN
   UPDATE Offspring						-- Update Offspring
   SET Offspring.IDSex = inserted.IDSex FROM inserted, deleted
   WHERE Offspring.IDLambKid = deleted.IDSheepGoat AND
	Offspring.IDSex = deleted.IDSex
END
GO

/*
UPDATE SheepGoat
    SET IDSex = "0"
	WHERE IDSheepGoat = "юб1110"
*/
GO
/*
UPDATE SheepGoat
    SET IDSheepGoat = "юб9110"--"юб1110"
	WHERE IDSheepGoat = "юб1110"--"юб9110"
*/
GO
