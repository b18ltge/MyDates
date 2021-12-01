-- L1, L2 --

--========--
-- buyers --
--========--

-- Table: public.buyers

-- DROP TABLE public.buyers;

CREATE TABLE IF NOT EXISTS public.buyers
(
    id integer NOT NULL DEFAULT nextval('buyers_id_seq'::regclass),
    name character varying(32) COLLATE pg_catalog."default" NOT NULL,
    phone character varying(15) COLLATE pg_catalog."default" NOT NULL,
    discount integer NOT NULL DEFAULT nextval('buyers_discount_seq'::regclass),
    CONSTRAINT buyers_pkey PRIMARY KEY (id),
    CONSTRAINT discount CHECK (discount < 100),
    CONSTRAINT phone CHECK (phone::text ~~ '+__(0__)_______'::text)
)

TABLESPACE pg_default;

ALTER TABLE public.buyers
    OWNER to postgres;



--=========--
-- product --
--=========--

-- Table: public.product

-- DROP TABLE public.product;

CREATE TABLE IF NOT EXISTS public.product
(
    id integer NOT NULL DEFAULT nextval('product_id_seq'::regclass),
    name character varying(65) COLLATE pg_catalog."default" NOT NULL,
    producer character varying(32) COLLATE pg_catalog."default" NOT NULL,
    weight smallint NOT NULL,
    ingredients character varying(256) COLLATE pg_catalog."default" NOT NULL,
    CONSTRAINT product_pkey PRIMARY KEY (id),
    CONSTRAINT weight CHECK (weight > 0)
)

TABLESPACE pg_default;

ALTER TABLE public.product
    OWNER to postgres;


--==============--
-- product_info --
--==============--

-- Table: public.product_info

-- DROP TABLE public.product_info;

CREATE TABLE IF NOT EXISTS public.product_info
(
    id integer NOT NULL DEFAULT nextval('product_count_id_seq'::regclass),
    product_id integer NOT NULL DEFAULT nextval('product_count_product_id_seq'::regclass),
    count smallint NOT NULL,
    end_date date NOT NULL,
    initial_price numeric(6,2) NOT NULL,
    price numeric(6,2) NOT NULL,
    CONSTRAINT product_count_pkey PRIMARY KEY (id),
    CONSTRAINT product_id FOREIGN KEY (product_id)
        REFERENCES public.product (id) MATCH SIMPLE
        ON UPDATE CASCADE
        ON DELETE CASCADE,
    CONSTRAINT count CHECK (count > 0),
    CONSTRAINT date CHECK (end_date > '2009-12-31'::date),
    CONSTRAINT initial_price CHECK (initial_price > 0::numeric),
    CONSTRAINT price CHECK (price > initial_price)
)

TABLESPACE pg_default;

ALTER TABLE public.product_info
    OWNER to postgres;



--===========--
-- purchases --
--===========--

-- Table: public.purchases

-- DROP TABLE public.purchases;

CREATE TABLE IF NOT EXISTS public.purchases
(
    id integer NOT NULL DEFAULT nextval('purchases_id_seq'::regclass),
    buyer_id integer NOT NULL DEFAULT nextval('purchases_buyer_id_seq'::regclass),
    product_id integer NOT NULL DEFAULT nextval('purchases_product_id_seq'::regclass),
    date date NOT NULL,
    count smallint NOT NULL,
    CONSTRAINT purchases_pkey PRIMARY KEY (id),
    CONSTRAINT buyer_id FOREIGN KEY (buyer_id)
        REFERENCES public.buyers (id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION,
    CONSTRAINT product_info_id FOREIGN KEY (product_id)
        REFERENCES public.product_info (id) MATCH SIMPLE
        ON UPDATE CASCADE
        ON DELETE CASCADE,
    CONSTRAINT date CHECK (date > '2009-12-31'::date),
    CONSTRAINT count CHECK (count > 0)
)

TABLESPACE pg_default;

ALTER TABLE public.purchases
    OWNER to postgres;



--===========--
-- suppliers --
--===========--


-- Table: public.suppliers

-- DROP TABLE public.suppliers;

CREATE TABLE IF NOT EXISTS public.suppliers
(
    id integer NOT NULL DEFAULT nextval('suppliers_id_seq'::regclass),
    name character varying(32) COLLATE pg_catalog."default" NOT NULL,
    town character varying(32) COLLATE pg_catalog."default" NOT NULL,
    phone character(15) COLLATE pg_catalog."default" NOT NULL,
    email character varying(32) COLLATE pg_catalog."default" NOT NULL,
    start_date date NOT NULL,
    CONSTRAINT suppliers_pkey PRIMARY KEY (id),
    CONSTRAINT email CHECK (email::text ~~ '%@%.%'::text),
    CONSTRAINT phone CHECK (phone ~~ '+__(0__)_______'::text),
    CONSTRAINT date CHECK (start_date > '2009-12-31'::date)
)

TABLESPACE pg_default;

ALTER TABLE public.suppliers
    OWNER to postgres;



--==========--
-- supplies --
--==========--


-- Table: public.supplies

-- DROP TABLE public.supplies;

CREATE TABLE IF NOT EXISTS public.supplies
(
    id integer NOT NULL DEFAULT nextval('supplies_id_seq'::regclass),
    supplier_id integer NOT NULL DEFAULT nextval('supplies_supplier_id_seq'::regclass),
    product_id integer NOT NULL DEFAULT nextval('supplies_product_id_seq'::regclass),
    date date NOT NULL,
    count smallint NOT NULL,
    price numeric(6,2),
    CONSTRAINT supplies_pkey PRIMARY KEY (id),
    CONSTRAINT product_id FOREIGN KEY (product_id)
        REFERENCES public.product (id) MATCH SIMPLE
        ON UPDATE CASCADE
        ON DELETE CASCADE,
    CONSTRAINT supplier_id FOREIGN KEY (supplier_id)
        REFERENCES public.suppliers (id) MATCH SIMPLE
        ON UPDATE CASCADE
        ON DELETE CASCADE,
    CONSTRAINT count CHECK (count > 0),
    CONSTRAINT price CHECK (price > 0::numeric)
)

TABLESPACE pg_default;

ALTER TABLE public.supplies
    OWNER to postgres;


