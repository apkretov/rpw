USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spUpdate_SumFlockManagm_SheepGoatDisp" AND type = "P")
DROP PROCEDURE spUpdate_SumFlockManagm_SheepGoatDisp
GO
CREATE PROCEDURE spUpdate_SumFlockManagm_SheepGoatDisp
AS
DECLARE @IDAgeSex1 AS char(1)
DECLARE @IDAgeSex2 AS char(1)
DECLARE @IDAgeSex3 AS char(1)
DECLARE @IDAgeSex4 AS char(1)
DECLARE @IDAgeSex5 AS char(1)
DECLARE @IDAgeSex6 AS char(1)
DECLARE @IDSexMale AS char(1)
DECLARE @IDSexFemale AS char(1)
SET DATEFORMAT dmy
SET @IDAgeSex1 = "1"
SET @IDAgeSex2 = "2"
SET @IDAgeSex3 = "3"
SET @IDAgeSex4 = "4"
SET @IDAgeSex5 = "5"
SET @IDAgeSex6 = "6"
SET @IDSexMale = "0"
SET @IDSexFemale = "1"
UPDATE SumFlockManagm_SheepGoatDisp -- Mark mature males.
SET IDAgeSex = @IDAgeSex1
WHERE CAST(DateDisp - DateBirth AS smallint) >=
   (SELECT Age FROM AgeSex WHERE IDAgeSex = @IDAgeSex1)AND 
   IDSex = @IDSexMale
UPDATE SumFlockManagm_SheepGoatDisp -- Mark mature females.
SET IDAgeSex = @IDAgeSex2
WHERE CAST(DateDisp - DateBirth AS smallint) >=
   (SELECT Age FROM AgeSex WHERE IDAgeSex = @IDAgeSex2) AND
   IDSex = @IDSexFemale
UPDATE SumFlockManagm_SheepGoatDisp -- Mark males > 1 year.
SET IDAgeSex = @IDAgeSex3
WHERE CAST(DateDisp - DateBirth AS smallint) >=
   (SELECT Age FROM AgeSex WHERE IDAgeSex = @IDAgeSex3) AND
   CAST(DateDisp - DateBirth AS smallint) <
   (SELECT Age FROM AgeSex WHERE IDAgeSex = @IDAgeSex1) AND
   IDSex = @IDSexMale
UPDATE SumFlockManagm_SheepGoatDisp -- Mark females > 1 year.
SET IDAgeSex = @IDAgeSex4
WHERE CAST(DateDisp - DateBirth AS smallint) >=
   (SELECT Age FROM AgeSex WHERE IDAgeSex = @IDAgeSex4) AND
   CAST(DateDisp - DateBirth AS smallint) <
   (SELECT Age FROM AgeSex WHERE IDAgeSex = @IDAgeSex2) AND
   IDSex = @IDSexFemale
UPDATE SumFlockManagm_SheepGoatDisp -- Mark males < 1 year.
SET IDAgeSex = @IDAgeSex5
WHERE CAST(DateDisp - DateBirth AS smallint) <
   (SELECT Age FROM AgeSex WHERE IDAgeSex = @IDAgeSex3) AND
   IDSex = @IDSexMale
UPDATE SumFlockManagm_SheepGoatDisp -- Mark females < 1 year.
SET IDAgeSex = @IDAgeSex6
WHERE CAST(DateDisp - DateBirth AS smallint) <
   (SELECT Age FROM AgeSex WHERE IDAgeSex = @IDAgeSex4) AND
   IDSex = @IDSexFemale
GO
spUpdate_SumFlockManagm_SheepGoatDisp 
GO
SELECT * FROM SumFlockManagm_SheepGoatDisp
GO