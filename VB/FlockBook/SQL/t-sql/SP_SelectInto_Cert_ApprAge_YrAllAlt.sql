USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_Cert_ApprAge_YrAllAlt" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_Cert_ApprAge_YrAllAlt
GO
CREATE PROCEDURE spSelectInto_Cert_ApprAge_YrAllAlt AS -- Allow nulls in Cert_ApprAge_YrAll.
    ALTER TABLE Cert_ApprAge_YrAll 
        ALTER COLUMN DateAppr smalldatetime NULL
    /*ALTER TABLE Cert_ApprAge_YrAll 
        ALTER COLUMN Leng real NULL*/
    ALTER TABLE Cert_ApprAge_YrAll 
        ALTER COLUMN Mass char(2) NULL
    ALTER TABLE Cert_ApprAge_YrAll 
        ALTER COLUMN Crimpins char(2) NULL
    ALTER TABLE Cert_ApprAge_YrAll 
        ALTER COLUMN Evens char(2) NULL
    /*ALTER TABLE Cert_ApprAge_YrAll 
        ALTER COLUMN Density smallint NULL*/
    ALTER TABLE Cert_ApprAge_YrAll 
        ALTER COLUMN Strength char(1) NULL
    ALTER TABLE Cert_ApprAge_YrAll 
        ALTER COLUMN Colour varchar(15) NULL
    ALTER TABLE Cert_ApprAge_YrAll 
        ALTER COLUMN Quality char(2) NULL
    ALTER TABLE Cert_ApprAge_YrAll 
        ALTER COLUMN FluffColour varchar(25) NULL
    /*ALTER TABLE Cert_ApprAge_YrAll 
        ALTER COLUMN Fluff tinyint NULL
    ALTER TABLE Cert_ApprAge_YrAll 
        ALTER COLUMN FibreYield tinyint NULL*/
    ALTER TABLE Cert_ApprAge_YrAll 
        ALTER COLUMN BodyType char(2) NULL
    ALTER TABLE Cert_ApprAge_YrAll 
        ALTER COLUMN Constitutn char(2) NULL
    ALTER TABLE Cert_ApprAge_YrAll 
        ALTER COLUMN BodySize char(2) NULL
    ALTER TABLE Cert_ApprAge_YrAll 
        ALTER COLUMN FatTail char(1) NULL
GO
spSelectInto_Cert_ApprAge_YrAllAlt
GO