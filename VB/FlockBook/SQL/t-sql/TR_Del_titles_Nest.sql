USE pubs
GO

IF EXISTS (SELECT name FROM sysobjects 		--Create trigger.
WHERE name = "Delete_Title" AND type = "TR")
DROP TRIGGER Delete_Title
GO
CREATE TRIGGER TR_on_titles
ON titles
FOR DELETE
AS 
PRINT "Here is the Deleted table:"		--View the Deleted table.
SELECT * FROM deleted
DELETE sales FROM sales, deleted		--Delete from the child tables.
WHERE sales.title_id = deleted.title_id
PRINT "Deleted from sales"
GO
CREATE TRIGGER TR_on_sales
ON sales
DELETE roysched FROM roysched, deleted
WHERE roysched.title_id = deleted.title_id 
PRINT "Deleted from roysched"
GO
CREATE TRIGGER TR_on_roysched
ON roysched
DELETE titleauthor FROM titleauthor, deleted
WHERE titleauthor.title_id = deleted.title_id 
PRINT "Deleted from titleauthor"
GO

DELETE titles WHERE title_id = "PS7777"		--Test deletion.
GO