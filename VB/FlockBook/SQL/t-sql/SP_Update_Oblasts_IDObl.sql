USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spUpdate_Oblasts_IDObl" AND type = "P")
    DROP PROCEDURE spUpdate_Oblasts_IDObl
GO
CREATE PROCEDURE spUpdate_Oblasts_IDObl (@IDOblast int, @IDCountry int, @Oblast varchar(50), 
    @Remark varchar(150)) AS
    UPDATE Oblasts
	SET IDCountry =@IDCountry, Oblast = @Oblast, Remark = @Remark
	WHERE IDOblast = @IDOblast 
GO
SELECT * FROM Oblasts 
GO
spUpdate_Oblasts_IDObl 9, 11, "1111adafad", "2222adsfaew"
GO
SELECT * FROM Oblasts 
GO