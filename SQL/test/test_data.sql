use test
begin tran

select top 5 
	c_addr
	,id
from test_data

/*
select ('abcdefghicde')
select replace('abcdefghicde','cde','xxx')
*/



rollback tran