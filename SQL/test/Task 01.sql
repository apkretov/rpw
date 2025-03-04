use test
begin tran

/*
-- Populata a test table.
set identity_insert test_data2 on -- Cannot insert explicit value for identity column in table 'table' when IDENTITY_INSERT is set to OFF @ https://stackoverflow.com/questions/1334012/cannot-insert-explicit-value-for-identity-column-in-table-table-when-identity
insert into test_data2(c_addr, id)
select top 3	
	-- tp.*,	
	td.*
	-- tp.c_name,
	-- tp.c_namerep,
	-- replace(td.c_addr, tp.c_name, tp.c_namerep) replaced
from T_Prepare as tp,
test_data as td
where td.c_addr like '% ' + tp.c_name + ' %'
set identity_insert test_data2 off -- Cannot insert explicit value for identity column in table 'table' when IDENTITY_INSERT is set to OFF @ https://stackoverflow.com/questions/1334012/cannot-insert-explicit-value-for-identity-column-in-table-table-when-identity
select * from test_data2
*/

select * from test_data2 -- The data before.

select tp.*, -- The replacements.
	td2.*,
	replace(td2.c_addr, tp.c_name, tp.c_namerep) as c_addr_replaced
from T_Prepare as tp, 
	test_data2 as td2
where td2.c_addr like '% ' + tp.c_name + ' %'

update test_data2 -- Update the data.
set c_addr = replace(tpR.c_addr, tpR.c_name, tpR.c_namerep)
from (
	select td.c_addr,
		tp.c_name, 
		tp.c_namerep
	from T_Prepare as tp, 
		test_data2 as td
	where td.c_addr like '% ' + tp.c_name + ' %'
) as tpR -- T_Prepare replacemnts

select * from test_data2 -- The data after.

rollback tran
-- commit tran