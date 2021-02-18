USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelect_ContrlParam" AND type = "P")
    DROP PROCEDURE spSelect_ContrlParam
GO
CREATE PROCEDURE spSelect_ContrlParam AS
    SELECT * FROM ContrlParam
GO
spSelect_ContrlParam
GO