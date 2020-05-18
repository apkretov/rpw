USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spUpdate_Countries_IDCountr" AND type = "P")
    DROP PROCEDURE spUpdate_Countries_IDCountr
GO
CREATE PROCEDURE spUpdate_Countries_IDCountr (@IDCountry int, @Country varchar(50), 
    @Remark varchar(150)) AS
    UPDATE Countries
	SET Country = @Country, Remark = @Remark
	WHERE IDCountry = @IDCountry 
GO
SELECT * FROM Countries 
GO
spUpdate_Countries_IDCountr 11, "Россия", "-"
GO
SELECT * FROM Countries 
GO