USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "trDel_SheepGoat" AND type = "TR")
    DROP TRIGGER trDel_SheepGoat -- Drop & create the trigger.
GO
CREATE TRIGGER trDel_Breeds ON Breeds FOR DELETE AS 
    DELETE StandWeight 						-- Delete StandWeight.
	FROM StandWeight, deleted			
	    WHERE StandWeight.IDBreed = deleted.IDBreed
    DELETE StandGrease 						-- Delete StandGrease.
	FROM StandGrease, deleted			
	    WHERE StandGrease.IDBreed = deleted.IDBreed
    DELETE StandLength 						-- Delete StandLength.
	FROM StandLength, deleted			
	    WHERE StandLength.IDBreed = deleted.IDBreed
    DELETE StandDiameter 					-- Delete StandDiameter.
	FROM StandDiameter, deleted			
	    WHERE StandDiameter.IDBreed = deleted.IDBreed
    DELETE StandFatTail 					-- Delete StandFatTail.
	FROM StandFatTail, deleted			
	    WHERE StandFatTail.IDBreed = deleted.IDBreed
GO