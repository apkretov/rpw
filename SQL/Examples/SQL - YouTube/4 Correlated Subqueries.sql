use Timber_2020_Test

select d.*
from Data as d
inner join (
	select UN_Country_Code,
		max(Year) as [year]
	from Data
	group by UN_Country_Code
) as max_years
	on d.UN_Country_Code = max_years.UN_Country_Code
		and d.Year = max_years.year
order by d.UN_Country_Code,
	d.Dimension_ID

select d1.*
from Data as d1
where d1.Year = (
	select max(d2.Year)
	from Data as d2
	where d2.UN_Country_Code = d1.UN_Country_Code
)
order by d1.UN_Country_Code,
	d1.Dimension_ID