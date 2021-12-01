-- 24.11.2021 (L3)

-- (#1)
-- Вилучення зв'язку між таблицями purchases та buyers
-- Вилучення зовнішнього ключа в таблиці purchases

--alter table purchases 
--drop CONSTRAINT buyer_id;

--alter table purchases 
--add CONSTRAINT buyer_id foreign key (buyer_id) references buyers (id);

-- (#2)
-- Видалення поля discount та зміна типу поля name в таблиці tmp_buyers

--alter table tmp_buyers
--drop column discount,
--alter column name type char(64);

--alter table tmp_buyers
--add column discount serial;

-- (#3)
-- Зміна типу поля name в product, а також встановлення обмеження NOT NULL

--alter table product
--alter column name type character varying(65),
--alter column name set not null;

-- (#4)
-- Додаванання нового поля (email) до таблиці tmp_buyers, а також додавання
-- до нього нового обмеження унікальності (UNIQUE)
--alter table tmp_buyers
--add column email character varying(64);

--create unique index email_id ON tmp_buyers (email);

--alter table tmp_buyers 
--add constraint email_id 
--unique using index email_id;

--alter table tmp_buyers
--drop column email;

-- (#5)
-- Зміна типу обмеження цілісності для зв'язку між таблицями purchases та buyers
--alter table purchases 
--drop CONSTRAINT buyer_id;

--alter table purchases
--add constraint buyer_id foreign key (buyer_id) references buyers (id)
--on update cascade
--on delete cascade;