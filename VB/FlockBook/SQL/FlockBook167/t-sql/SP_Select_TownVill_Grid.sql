USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_TownVill_Grid" AND type = "P")
    DROP PROCEDURE spSelect_TownVill_Grid
GO
CREATE PROCEDURE spSelect_TownVill_Grid (@Rayon varchar(50)) AS
    SELECT /*Rayons.Rayon AS �����,*/ TownVill.TownVill AS [��������� �����]/*[��������� ������]*//*, TownVill.Remark AS 
	�������*/
	FROM TownVill INNER JOIN Rayons ON 
	    TownVill.IDRayon = Rayons.IDRayon
	WHERE Rayons.Rayon = @Rayon
	ORDER BY TownVill.TownVill
GO
spSelect_TownVill_Grid "����01"
GO

