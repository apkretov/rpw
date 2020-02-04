USE MyDB
GO

IF EXISTS (SELECT name FROM sysobjects 		--Create table.
WHERE name = "MyTable" AND type = "U")
DROP TABLE MyTable
GO
CREATE TABLE MyTable 				
(column1 smallint, column2 char(10),)
GO

IF EXISTS (SELECT name FROM sysobjects 		--Create trigger.
WHERE name = "Print_Update" AND type = "TR")
DROP TRIGGER Print_Update
GO
CREATE TRIGGER Print_Update
ON MyTable
FOR UPDATE
AS 
PRINT "MyTable was updated"
GO

INSERT INTO MyTable VALUES (1, "row one")	--Insert & update values.
GO
UPDATE MyTable SET column2 = "ROW 1" 
WHERE column2 = "row one"
GO 