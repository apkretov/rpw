USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spUpdate_Rayons_IDRayn" AND type = "P")
    DROP PROCEDURE spUpdate_Rayons_IDRayn
GO
CREATE PROCEDURE spUpdate_Rayons_IDRayn (@IDRayon int, @IDOblast int, @Rayon varchar(50), 
    @Remark varchar(150)) AS
    UPDATE Rayons
	SET IDOblast =@IDOblast, Rayon = @Rayon, Remark = @Remark
	WHERE IDRayon = @IDRayon 
GO
SELECT * FROM Rayons 
GO
spUpdate_Rayons_IDRayn 9, 2, "999999", "99999999"
GO
SELECT * FROM Rayons 
GO