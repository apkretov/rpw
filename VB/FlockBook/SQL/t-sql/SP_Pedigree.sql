--use Test
--use FlockBookRec
--go
--CREATE PROCEDURE spPedigree (@DigitDam char(2), @DigitSG char(2))
--AS
--update SheepGoat
-- Step 1.
--set IDSire = left(IDSheepGoat, 4) + "00" 
--set IDDam = @DigitDam

--Step 2.
--set IDSire = left(IDSheepGoat,2) + IDSire 
--set IDDam = left(IDSheepGoat,4) + IDDam

-- Step 3.
--set IDSire = "", IDDam = ""
--where right(IDSheepGoat,2) < "02"
--go