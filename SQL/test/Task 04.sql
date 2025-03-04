use test
begin tran

/*
select * from test_data -- The data before.
go
*/

select top 3 -- The replacements.
	tp.*,
	td2.*,
	replace(td2.c_addr, tp.c_name, tp.c_namerep) as c_addr_replaced
from T_Prepare as tp, 
	test_data as td2
-- where td2.c_addr like '% ' + tp.c_name + ' %'
where (
	-------------if 
)

go

/*
update test_data -- Update the data.
set c_addr = replace(tpR.c_addr, tpR.c_name, tpR.c_namerep)
from (
	select td.c_addr,
		td.id,
		tp.c_name, 
		tp.c_namerep
	from T_Prepare as tp, 
		test_data as td
	where td.c_addr like '% ' + tp.c_name + ' %'
) as tpR -- The T_Prepare-replacemnts table.
where test_data.id = tpR.id
go

select * from test_data -- The data after.
go
*/

rollback tran