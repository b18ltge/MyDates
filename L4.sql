-- 17.11.2021 (L4)

-- (#4)
-- Видалення записів з таблиці buyers.
delete from buyers where id > 1;

-- (#1)
-- Заповнення таблиці buyers в режимі одиночного і групового доповнення.
insert into buyers values (2, 'buyer2' , '+38(099)1112222', 0);

insert into buyers 
values (3, 'buyer3', '+38(099)1112233',0), (4, 'buyer3', '+38(099)1112244', 0);

-- (#2)
-- Заповнення таблиці buyers даними з текстового файлу.
copy buyers from 'D:\PostgreSQL/My Files/MyFile.txt' ( delimiter('|') );

-- (#3)
-- Модифікація значень у таблиці buyers для одного поля та для групи полів 
-- за певною умовою.
update buyers set discount = 5
where id = 4;

update buyers set discount = 0
where id > 4;

