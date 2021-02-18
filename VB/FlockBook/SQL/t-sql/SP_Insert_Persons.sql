USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spInsert_Persons" AND type = "P")
    DROP PROCEDURE spInsert_Persons
GO
CREATE PROCEDURE spInsert_Persons (@Nam varchar(100), @IDTownVill int, @Address varchar(150), 
    @Phone varchar(50), @Email varchar(50), @Remark varchar(150)) AS
    INSERT INTO Persons (Nam, IDTownVill, Address, Phone, Email, Remark)
	VALUES (@Nam, @IDTownVill, @Address, @Phone, @Email, @Remark)
GO
SELECT * FROM Persons
GO
spInsert_Persons "KD, FAD, SF", 1, 
    "K. D; ;; , , , HA 2324 JXHD 5993JAKD 90383 AKD", "5455-5645-5454", 
    "sasha_durham@hotmail.com", "KDJA, JA, AJDJF,DJFJ"
GO
SELECT * FROM Persons
GO