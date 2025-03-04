use Timber_2020_Test
select c1.COUNTRY_NAME as c1_COUNTRY_NAME,
	c2.COUNTRY_NAME as c2_COUNTRY_NAME
from Countries as c1
	join Countries as c2 
		on c1.COUNTRY_NAME < c2.COUNTRY_NAME
--where c1.COUNTRY_NAME = 'Albania' -- 45
						--'Andorra' -- 44
						--'Austria' -- 43
						--'Ukraine' -- 1
						--'United Kingdom' -- 0
order by c1.COUNTRY_NAME, c2.COUNTRY_NAME