USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spDelete_Rayons_IDRayn" AND type = "P")
    DROP PROCEDURE spDelete_Rayons_IDRayn
GO
CREATE PROCEDURE spDelete_Rayons_IDRayn (@IDRayon int) AS
    DELETE Rayons
	WHERE IDRayon = @IDRayon
GO
spDelete_Rayons_IDRayn 8
GO
