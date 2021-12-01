-- 24.11.2021 (L5)

-- (#1)
-- Запит на виконання об'єднання (UNION) & (UNION ALL) , inner, left, right:

--select name from buyers
--union
--select name from tmp_buyers;

--select buyers.name,phone from buyers
--inner join tmp_buyers on buyers.id = tmp_buyers.id;

--select buyers.name,phone from buyers
--left join tmp_buyers on buyers.id = tmp_buyers.id;

--select buyers.name,phone from buyers
--right join tmp_buyers on buyers.id = tmp_buyers.id;

-- (#2)
-- Запит на виконання перетину (INTERSECT):

--select name from buyers
--intersect
--select name from tmp_buyers;


-- (#3)
-- Запит на побудову різниці (EXCEPT):		[minus]

--select name from buyers
--except
--select name from tmp_buyers;

-- (#4)
-- Запит на виконання декартового добутку двох таблиць (CARTESIAN JOIN): [Cross Join]

select buyers.name from buyers
cross join tmp_buyers;