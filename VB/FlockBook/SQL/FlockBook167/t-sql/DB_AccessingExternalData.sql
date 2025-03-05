USE master
GO

/*
sp_addlinkedserver @server = N'LinkServerLogic',
    @srvproduct = N' ',
    @provider = N'SQLOLEDB', 
    @datasrc = N'Logic', 
    @catalog = N'Northwind'
*/
--GO
/*
SELECT *
FROM LinkServerLogic.Northwind.dbo.Shippers
*/
--GO


sp_addlinkedserver 'Nwind8', 'Access 97', 'Microsoft.Jet.OLEDB.4.0', 
    'D:\CABS\SQL\Databases\Nwind\Nwind.mdb' 

GO

sp_addlinkedsrvlogin 'Nwind8', false, 'sa', 'Admin', NULL -- Add user 'sa'.

GO

SELECT * 		-- Does't work.
FROM Nwind8...Employees

GO

/*
sp_addlinkedserver N'Excel1', N'Jet 4.0', N'Microsoft.Jet.OLEDB.4.0',
    N'D:\CABS\SQL\Databases\Nwind\MySheet.xls', NULL, N'Excel 5.0'
*/
--GO
/*
sp_addlinkedsrvlogin N'Excel1', false, sa, N'ADMIN', NULL
*/
--GO

/*
SELECT * 		-- Does't work.
FROM Excel...Territories
*/
--GO

/*
EXEC sp_addserver 'RPCothersite' -- Create a remote server definition using a pseudoname.
*/
GO
/*
EXEC sp_setnetname 'RPCothersite1', 'othersite' -- Set the pseudoname to the network name faraway. 
*/
--GO
/*
-- A remote procedure call to the othersite server.
EXEC RPCothersite1.master.dbo.sp_who   -- Doesn't work.
*/
--GO
