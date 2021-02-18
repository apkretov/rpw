USE Test
--USE FlockBookRec
GO
--CREATE PROCEDURE spInsert_WeightWool @IDSheepGoat char(6)
--AS
--INSERT INTO WeightWool
--(IDSheepGoat, WtBirth, DateWean, WtWean, Date7Mon, Wt7Mon, Date1Yr, Wt1Yr, 
--	DateShear, Grease, Leng, Diam)
--VALUES (@IDSheepGoat, 8, getdate(), 20, getdate(), 40, getdate(), 55,
--	getdate(), 4, 9, 25)
--GO
spInsert_WeightWool "¿¿0001"
GO