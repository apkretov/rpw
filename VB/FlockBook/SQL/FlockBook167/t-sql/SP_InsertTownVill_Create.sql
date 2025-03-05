USE Test
GO
CREATE PROCEDURE spInsertTownVill (@IDRayon char(6), @IDTownVill char(6), 
@TownVill char(25))
AS
INSERT INTO TownVill
(IDRayon, IDTownVill, TownVill)
VALUES (@IDRayon, @IDTownVill, @TownVill)
GO