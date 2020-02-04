USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spUpdate_SumPerform_SheepGoat" AND 
    type = "P")
    DROP PROCEDURE spUpdate_SumPerform_SheepGoat
GO
CREATE PROCEDURE spUpdate_SumPerform_SheepGoat @Date varchar(8) AS
    DECLARE @IDAgeSex1 AS char(1)
    DECLARE @IDAgeSex2 AS char(1)
    DECLARE @IDAgeSex3 AS char(1)
    DECLARE @IDAgeSex4 AS char(1)
    DECLARE @IDAgeSex5 AS char(1)
    DECLARE @IDAgeSex6 AS char(1)
    DECLARE @IDSexMale AS char(1)
    DECLARE @IDSexFemale AS char(1)
    DECLARE @DateConv AS smalldatetime
    SET DATEFORMAT dmy
    SET @IDAgeSex1 = "1"
    SET @IDAgeSex2 = "2"
    SET @IDAgeSex3 = "3"
    SET @IDAgeSex4 = "4"
    SET @IDAgeSex5 = "5"
    SET @IDAgeSex6 = "6"
    SET @IDSexMale = "0"
    SET @IDSexFemale = "1"
    SET @DateConv = CAST(@Date AS smalldatetime)
    UPDATE SumPerform_SheepGoat -- Mark mature males.
        SET IDAgeSex = @IDAgeSex1
        WHERE @DateConv - DateBirth >= (SELECT Age FROM AgeSex WHERE IDAgeSex = @IDAgeSex1) AND 
            IDSex = @IDSexMale
    UPDATE SumPerform_SheepGoat -- Mark mature females.
        SET IDAgeSex = @IDAgeSex2
        WHERE @DateConv - DateBirth >= (SELECT Age FROM AgeSex WHERE IDAgeSex = @IDAgeSex2) AND
            IDSex = @IDSexFemale
    UPDATE SumPerform_SheepGoat -- Mark males > 1 year.
        SET IDAgeSex = @IDAgeSex3
        WHERE @DateConv - DateBirth >= (SELECT Age FROM AgeSex WHERE IDAgeSex = @IDAgeSex3) AND
            @DateConv - DateBirth < (SELECT Age FROM AgeSex WHERE IDAgeSex = @IDAgeSex1) AND
            IDSex = @IDSexMale
    UPDATE SumPerform_SheepGoat -- Mark females > 1 year.
        SET IDAgeSex = @IDAgeSex4
        WHERE @DateConv - DateBirth >= (SELECT Age FROM AgeSex WHERE IDAgeSex = @IDAgeSex4) AND
            @DateConv - DateBirth < (SELECT Age FROM AgeSex WHERE IDAgeSex = @IDAgeSex2) AND
            IDSex = @IDSexFemale
    UPDATE SumPerform_SheepGoat -- Mark males < 1 year.
        SET IDAgeSex = @IDAgeSex5
        WHERE @DateConv - DateBirth < (SELECT Age FROM AgeSex WHERE IDAgeSex = @IDAgeSex3) AND
            IDSex = @IDSexMale
    UPDATE SumPerform_SheepGoat -- Mark females < 1 year.
        SET IDAgeSex = @IDAgeSex6
        WHERE @DateConv - DateBirth < (SELECT Age FROM AgeSex WHERE IDAgeSex = @IDAgeSex4) AND
            IDSex = @IDSexFemale
GO
spUpdate_SumPerform_SheepGoat "29.01.03"
GO
SELECT * FROM SumPerform_SheepGoat
GO