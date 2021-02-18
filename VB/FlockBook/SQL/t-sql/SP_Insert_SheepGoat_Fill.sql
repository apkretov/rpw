--use FlockBookRec
USE Test
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spInsert_SheepGoat_Fill" 
AND type = "P")
DROP PROCEDURE spInsert_SheepGoat_Fill
GO
CREATE PROCEDURE spInsert_SheepGoat_Fill (@IDFarm char(2), @IDSheepGoat char(6))
--CREATE PROCEDURE spInsertSheepGoat @IDSheepGoat char(6)
--CREATE PROCEDURE spInsertSheepGoat
AS
INSERT INTO SheepGoat
(IDFarm, IDSheepGoat, IDSex, IDBreedBase, BreedCross, DateBirth, IDFarmBirth, TypeBirth, IDSire, IDDam, DateDisp, IDDispReas, Remark)
VALUES (@IDFarm, @IDSheepGoat, "1", " »", " »", getdate(), "¿¿", 1, "", "", getdate(), "00", "")
--VALUES ("¿¿", @IDSheepGoat, "1", " »", " »", getdate(), "¿¿", 1, "", "", getdate(), "00", "")
--VALUES ("¿¿", "¿¿0017", "1", " »", " »", getdate(), "¿¿", 1, "", "", getdate(), "00", "")
GO