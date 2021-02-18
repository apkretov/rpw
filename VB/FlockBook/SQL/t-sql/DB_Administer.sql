USE master
GO

/*
BACKUP DATABASE [FlockBook]
    TO DISK = 'D:\CABS\SQL\Databases\FlockBook\backup\FlockBook.bak'
	WITH INIT
*/
/*
BACKUP DATABASE [Племкнига]
    TO DISK = 'D:\CABS\SQL\Databases\FlockBook\backup\Племкнига.bak'
	WITH INIT
*/
--GO

/*
RESTORE DATABASE [FlockBook Copy]  -- Restore the files for FlockBookCopy.
    FROM DISK = 'D:\CABS\SQL\Databases\FlockBook\backup\FlockBook.bak'
    	WITH MOVE 'FlockBook_root' TO 'D:\CABS\SQL\Databases\FlockBookCopy\data\FlockBook_root.mdf', 
    	    MOVE 'FlockBook_data1' TO 'D:\CABS\SQL\Databases\FlockBookCopy\data\FlockBook_data1.ndf',
    	    MOVE 'FlockBookLog_data1' TO 
		'D:\CABS\SQL\Databases\FlockBookCopy\data\FlockBook_logdata1.ldf' 
*/
--GO

--EXEC sp_addlogin 'UzerZ', 'PwdZ'
--EXEC sp_droplogin 'UzerZ'
--SELECT name FROM syslogins WHERE name IS NOT NULL
--EXEC sp_helplogins
--EXEC sp_helpuser
--EXEC sp_addsrvrolemember 'user1', 'sysadmin'
--GO

/*
sp_detach_db [FlockBook Copy]
*/
--GO

/*CREATE DATABASE Archive
ON PRIMARY (FILENAME = 'D:\CABS\SQL\Databases\Archive\data\archdat1.mdf')
FOR ATTACH*/
--GO

/*
sp_attach_db @dbname = N'Archive', 
    @filename1 = N'D:\CABS\SQL\Databases\Archive\data\archdat1.mdf', 
    @filename2 = N'D:\CABS\SQL\Databases\Archive\data\archdat2.ndf',
    @filename3 = N'D:\CABS\SQL\Databases\Archive\data\archdat3.ndf',
    @filename4 = N'D:\CABS\SQL\Databases\Archive\data\archlog1.ldf',
    @filename5 = N'D:\CABS\SQL\Databases\Archive\data\archlog2.ldf'
*/
--GO

/*
sp_create_removable 'inventory_Copy', 
  'invsys','D:\CABS\SQL\Databases\inventory\data\invsys.mdf', 2, 
  'invlog', 'D:\CABS\SQL\Databases\inventory\data\invlog.ldf',4,
  'invdata','D:\CABS\SQL\Databases\inventory\data\invdata.ndf',10
*/
--GO

/*
sp_helpdb FlockBook
*/
/*
sp_helpdb 
*/
--GO
