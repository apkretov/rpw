use Timber_2020_Test

select * 
from Countries as c
where exists (
	select *
	from Data as d
	where d.UN_Country_Code = c.UN_COUNTRY_CODE
	)