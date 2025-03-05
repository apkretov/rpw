-- Step 5.
--USE Test
USE FlockBookRec
GO
CREATE PROCEDURE spInsert_Offspring (@IDDam char(6), @Cycle tinyint, 
	@IDLambKid char(6))
AS
INSERT INTO Offspring
(IDDam, Cycle, IDLambKid, IDLiv)
VALUES (@IDDam, @Cycle, @IDLambKid, "-")
GO
--spInsert_Offspring "¿¿0001", 1, "¿¿0002"
--GO