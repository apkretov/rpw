USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "trUpd_Breeds" AND type = "TR") 
    DROP TRIGGER trUpd_Breeds 
GO
CREATE TRIGGER trUpd_Breeds ON Breeds FOR UPDATE AS 
    IF UPDATE (IDBreed)
	BEGIN
   	UPDATE StandWeight 					-- Update StandWeight
   	    SET StandWeight.IDBreed = inserted.IDBreed 
		FROM inserted, deleted
   		WHERE StandWeight.IDBreed = deleted.IDBreed
   	UPDATE StandGrease 					-- Update StandGrease
   	    SET StandGrease.IDBreed = inserted.IDBreed 
		FROM inserted, deleted
   		WHERE StandGrease.IDBreed = deleted.IDBreed
   	UPDATE StandLength 					-- Update StandLength
   	    SET StandLength.IDBreed = inserted.IDBreed 
		FROM inserted, deleted
   		WHERE StandLength.IDBreed = deleted.IDBreed
   	UPDATE StandDiameter 					-- Update StandDiameter
   	    SET StandDiameter.IDBreed = inserted.IDBreed 
		FROM inserted, deleted
   		WHERE StandDiameter.IDBreed = deleted.IDBreed
   	UPDATE StandFatTail 					-- Update StandFatTail
   	    SET StandFatTail.IDBreed = inserted.IDBreed 
		FROM inserted, deleted
   		WHERE StandFatTail.IDBreed = deleted.IDBreed
	END     
GO
