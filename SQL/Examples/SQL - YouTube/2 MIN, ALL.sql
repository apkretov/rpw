use Timber_2020_Test
go

select top 1000 * 
from Data
where Value = (
	select min(Value)
	from Data
	)

select * 
from Data
where Value <= all (
	select Value 
	from Data
	)