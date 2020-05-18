USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spInsert_TownVill" AND type = "P")
    DROP PROCEDURE spInsert_TownVill
GO
CREATE PROCEDURE spInsert_TownVill (@IDRayon int, @TownVill varchar(50), @Remark varchar(150)) AS
    INSERT INTO TownVill (IDRayon, TownVill, Remark)
	VALUES (@IDRayon, @TownVill, @Remark)
GO
SELECT * FROM TownVill
GO
spInsert_TownVill 1, "KDFADSF", "ADSFASD"
GO
SELECT * FROM TownVill
GO