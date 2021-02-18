USE master 
GO 
CREATE DATABASE MyDB
ON			
(NAME = MyDB_root,		-- Main data file.
FILENAME = "d:\cabs\sql\Databases\MyDB\data\MyDB_root.mdf",
SIZE = 10MB,
MAXSIZE = 100MB,
FILEGROWTH = 1MB),
(NAME = MyDB_data1,	-- Additional data file.
FILENAME = "d:\cabs\sql\Databases\MyDB\data\MyDB_data1.ndf",
SIZE = 10MB,
MAXSIZE = 100MB,
FILEGROWTH = 1MB)
LOG ON
(NAME = Log_data1,		-- Transaction log file.
FILENAME = "d:\cabs\sql\Databases\MyDB\log_files\log_data1.ldf",
SIZE = 10MB,
MAXSIZE = 100MB,
FILEGROWTH = 1MB)
GO

-- Set options.
USE MyDB
GO
EXEC sp_dboption 'MyDB', 'select into', 'TRUE' -- Allow The SELECT INTO statement.
GO
