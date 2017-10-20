USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelect_Busy" AND type = "P")
    DROP PROCEDURE spSelect_Busy
GO
CREATE PROCEDURE spSelect_Busy AS
    SELECT * FROM Busy
GO 
spSelect_Busy
GO