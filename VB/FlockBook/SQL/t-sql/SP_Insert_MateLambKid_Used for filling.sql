-- Step 4.
--USE Test
USE FlockBookRec
GO
CREATE PROCEDURE spInsert_MateLambKid (@IDDam char(6), @Cycle tinyint, 
	@IDSire char(6))
AS
SET DATEFORMAT dmy
INSERT INTO MateLambKid
(IDDam, Cycle, DateMatFrom, DateMatTo, IDSire, DateLambKid, TypeBirth)
VALUES (@IDDam, @Cycle,  getdate(), getdate(), @IDSire, getdate(), 1)
GO
--spInsert_MateLambKid "¿¿0001", 1, "¿¿0000"
--GO