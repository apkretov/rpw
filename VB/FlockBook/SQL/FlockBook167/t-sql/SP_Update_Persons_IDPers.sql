USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spUpdate_Persons_IDPers" AND type = "P")
    DROP PROCEDURE spUpdate_Persons_IDPers
GO
CREATE PROCEDURE spUpdate_Persons_IDPers (@IDPers int, @Nam varchar(100), @IDTownVill int, 
    @Address varchar(150), @Phone varchar(50), @Email varchar(50), @Remark varchar(150)) AS
    UPDATE Persons
	SET Nam = @Nam, IDTownVill = @IDTownVill, Address = @Address, Phone = @Phone, 
	    Email = @Email, Remark = @Remark
	WHERE IDPers = @IDPers 
GO
SELECT * FROM Persons 
GO
spUpdate_Persons_IDPers 6, "99999999", 1, "99999999", "999999999", "9999999", "999999999"
GO
SELECT * FROM Persons 
GO