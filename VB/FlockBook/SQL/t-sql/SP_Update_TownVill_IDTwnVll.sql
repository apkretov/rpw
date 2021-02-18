USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spUpdate_TownVill_IDTwnVll" AND type = "P")
    DROP PROCEDURE spUpdate_TownVill_IDTwnVll
GO
CREATE PROCEDURE spUpdate_TownVill_IDTwnVll (@IDTownVill int, @IDRayon int, 
    @TownVill varchar(50), @Remark varchar(150)) AS
    UPDATE TownVill
	SET IDRayon = @IDRayon, TownVill = @TownVill, Remark = @Remark
	WHERE IDTownVill = @IDTownVill 
GO
SELECT * FROM TownVill 
GO
spUpdate_TownVill_IDTwnVll 34, 1, "000000", "00000000"
GO
SELECT * FROM TownVill 
GO