USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelect_CopmClass" AND type = "P")
    DROP PROCEDURE spSelect_CopmClass
GO
CREATE PROCEDURE spSelect_CopmClass AS
    SELECT * FROM CopmClass
GO
spSelect_CopmClass 
GO