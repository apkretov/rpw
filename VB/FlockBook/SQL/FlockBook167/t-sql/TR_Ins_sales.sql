USE pubs
GO

IF EXISTS (SELECT name FROM sysobjects 			--Create trigger.
WHERE name = "Update_ytd_sales" AND type = "TR")
DROP TRIGGER Update_ytd_sales
GO
CREATE TRIGGER Update_ytd_sales
ON sales
FOR INSERT
AS 
PRINT "Here is the Inserted table:"			--View the Inserted table.
SELECT * FROM inserted 
UPDATE titles SET ytd_sales = ytd_sales + qty
FROM inserted 
WHERE titles.title_id = inserted.title_id
GO
INSERT INTO sales VALUES  				--Test deletion.
   (7066, 1, "July 3, 1999", 100, "Net 30", "BU1111")
GO