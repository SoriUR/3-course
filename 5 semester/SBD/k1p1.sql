/**
 * Создание типа и таблиц
 */
CREATE OR REPLACE TYPE l2_name_type AS OBJECT(
first_name   VARCHAR2(40),
second_name VARCHAR2(40),
last_name VARCHAR2(40),
MEMBER FUNCTION get_fullname RETURN VARCHAR2
);

CREATE OR REPLACE TYPE BODY l2_name_type AS
MEMBER FUNCTION get_fullname RETURN VARCHAR2 IS
    fullname VARCHAR2(120);
    BEGIN
			fullname := SELF.first_name || ' ' || SELF.second_name || ' ' || SELF.last_name;
			RETURN fullname;
    END;
END;
/

CREATE TABLE l2_animal (
	id INT NOT NULL,
	type INT NOT NULL,
	aviary INT NOT NULL,
	image INT,
	PRIMARY KEY (id)
);

CREATE TABLE l2_image (
	id INT NOT NULL,
	photo blob,
	PRIMARY KEY (id)
)

CREATE TABLE l2_staff (
	id INT NOT NULL,
	name l2_name_type NOT NULL,
	image INT,
	job INT NOT NULL,
	PRIMARY KEY (id)
);

CREATE TABLE l2_aviary (
	id INT NOT NULL,
	type INT NOT NULL,
	zoo_part INT NOT NULL,
	PRIMARY KEY (id)
);

CREATE TABLE l2_aviary_type (
	id INT NOT NULL,
	name varchar(100) NOT NULL,
	PRIMARY KEY (id)
);

CREATE TABLE l2_animal_type (
	id INT NOT NULL,
	name varchar(100) NOT NULL,
	animal_class INT NOT NULL,
	PRIMARY KEY (id)
);

CREATE TABLE l2_animal_class (
	id INT NOT NULL,
	name varchar(100) NOT NULL,
	PRIMARY KEY (id)
);

CREATE TABLE l2_aviary_staff (
	id INT NOT NULL,
	staff_id INT NOT NULL,
	aviary_id INT NOT NULL,
	PRIMARY KEY (id)
);

CREATE TABLE l2_food (
	id INT NOT NULL,
	animal_class INT NOT NULL,
	name varchar(100) NOT NULL,
	PRIMARY KEY (id)
);

CREATE TABLE l2_staff_job (
	id INT NOT NULL,
	name varchar(100) NOT NULL,
	salary INT NOT NULL,
	PRIMARY KEY (id)
);

CREATE TABLE l2_zoo_part (
	id INT NOT NULL,
	name varchar(100) NOT NULL,
	PRIMARY KEY (id)
);

ALTER TABLE l2_animal ADD CONSTRAINT l2_animal_fk0 FOREIGN KEY (type) REFERENCES l2_animal_type(id) ON DELETE CASCADE;

ALTER TABLE l2_animal ADD CONSTRAINT l2_animal_fk1 FOREIGN KEY (aviary) REFERENCES l2_aviary(id) ON DELETE CASCADE;

ALTER TABLE l2_animal ADD CONSTRAINT l2_animal_fk2 FOREIGN KEY (image) REFERENCES l2_image(id) ON DELETE CASCADE;

ALTER TABLE l2_staff ADD CONSTRAINT l2_staff_fk0 FOREIGN KEY (job) REFERENCES l2_staff_job(id) ON DELETE CASCADE;

ALTER TABLE l2_staff ADD CONSTRAINT l2_staff_fk1 FOREIGN KEY (image) REFERENCES l2_image(id) ON DELETE CASCADE;

ALTER TABLE l2_aviary ADD CONSTRAINT l2_aviary_fk0 FOREIGN KEY (type) REFERENCES l2_aviary_type(id) ON DELETE CASCADE;

ALTER TABLE l2_aviary ADD CONSTRAINT l2_aviary_fk1 FOREIGN KEY (zoo_part) REFERENCES l2_zoo_part(id) ON DELETE CASCADE;

ALTER TABLE l2_animal_type ADD CONSTRAINT l2_animal_type_fk0 FOREIGN KEY (animal_class) REFERENCES l2_animal_class(id) ON DELETE CASCADE;

ALTER TABLE l2_food ADD CONSTRAINT l2_food_fk0 FOREIGN KEY (animal_class) REFERENCES l2_animal_class(id) ON DELETE CASCADE;

ALTER TABLE l2_aviary_staff ADD CONSTRAINT l2_aviary_staff_fk0 FOREIGN KEY (aviary_id) REFERENCES l2_aviary(id) ON DELETE CASCADE;

ALTER TABLE l2_aviary_staff ADD CONSTRAINT l2_aviary_staff_fk1 FOREIGN KEY (staff_id) REFERENCES l2_staff(id) ON DELETE CASCADE;
/**
 * Создание сиквенсов
 */
DROP SEQUENCE L2_ANIMAL_SEQ;
DROP SEQUENCE L2_ANIMAL_CLASS_SEQ;
DROP SEQUENCE L2_ANIMAL_TYPE_SEQ;
DROP SEQUENCE L2_AVIARY_SEQ;
DROP SEQUENCE L2_AVIARY_STAFF_SEQ;
DROP SEQUENCE L2_AVIARY_TYPE_SEQ;
DROP SEQUENCE L2_FOOD_SEQ;
DROP SEQUENCE L2_STAFF_JOB_SEQ;
DROP SEQUENCE L2_STAFF_SEQ;
DROP SEQUENCE L2_ZOO_PART_SEQ;


CREATE SEQUENCE l2_animal_seq
START WITH 1
INCREMENT BY 1
NOMAXVALUE;
/
CREATE SEQUENCE l2_staff_seq
START WITH 1
INCREMENT BY 1
NOMAXVALUE;
/
CREATE SEQUENCE l2_aviary_seq
START WITH 1
INCREMENT BY 1
NOMAXVALUE;
/
CREATE SEQUENCE l2_aviary_type_seq
START WITH 1
INCREMENT BY 1
NOMAXVALUE;
/
CREATE SEQUENCE l2_animal_type_seq
START WITH 1
INCREMENT BY 1
NOMAXVALUE;
/
CREATE SEQUENCE l2_animal_class_seq
START WITH 1
INCREMENT BY 1
NOMAXVALUE;
/
CREATE SEQUENCE l2_aviary_staff_seq
START WITH 1
INCREMENT BY 1
NOMAXVALUE;
/
CREATE SEQUENCE l2_food_seq
START WITH 1
INCREMENT BY 1
NOMAXVALUE;
/
CREATE SEQUENCE l2_staff_job_seq
START WITH 1
INCREMENT BY 1
NOMAXVALUE;
/
CREATE SEQUENCE l2_zoo_part_seq
START WITH 1
INCREMENT BY 1
NOMAXVALUE;
/

CREATE SEQUENCE l2_image_seq
START WITH 1
INCREMENT BY 1
NOMAXVALUE;
/

/**
 * Создание тригерров
 */
CREATE or REPLACE TRIGGER l2_animal_trg
before insert on l2_animal
for each row
  begin
    if :new.id is null then
      select l2_animal_seq.nextval into :new.id from dual;
    end if;
  end;
/
CREATE or REPLACE TRIGGER l2_staff_trg
before insert on l2_staff
for each row
  begin
    if :new.id is null then
      select l2_staff_seq.nextval into :new.id from dual;
    end if;
  end;
/
CREATE or REPLACE TRIGGER l2_aviary_trg
before insert on l2_aviary
for each row
  begin
    if :new.id is null then
      select l2_aviary_seq.nextval into :new.id from dual;
    end if;
  end;
/
CREATE or REPLACE TRIGGER l2_aviary_type_trg
before insert on l2_aviary_type
for each row
  begin
    if :new.id is null then
      select l2_aviary_type_seq.nextval into :new.id from dual;
    end if;
  end;
/
CREATE or REPLACE TRIGGER l2_animal_type_trg
before insert on l2_animal_type
for each row
  begin
    if :new.id is null then
      select l2_animal_type_seq.nextval into :new.id from dual;
    end if;
  end;
/
CREATE or REPLACE TRIGGER l2_animal_class_trg
before insert on l2_animal_class
for each row
  begin
    if :new.id is null then
      select l2_animal_class_seq.nextval into :new.id from dual;
    end if;
  end;
/
CREATE or REPLACE TRIGGER l2_aviary_staff_trg
before insert on l2_aviary_staff
for each row
  begin
    if :new.id is null then
      select l2_aviary_staff_seq.nextval into :new.id from dual;
    end if;
  end;
/
CREATE or REPLACE TRIGGER l2_food_trg
before insert on l2_food
for each row
  begin
    if :new.id is null then
      select l2_food_seq.nextval into :new.id from dual;
    end if;
  end;
/
CREATE or REPLACE TRIGGER l2_staff_job_trg
before insert on l2_staff_job
for each row
  begin
	if ((:new.salary is null) or (:new.salary < 0)) then
     	select 10000 into :new.salary from dual;
    end if;
    if :new.id is null then
      select l2_staff_job_seq.nextval into :new.id from dual;
    end if;
  end;
/
CREATE or REPLACE TRIGGER l2_zoo_part_trg
before insert on l2_zoo_part
for each row
  begin
    if :new.id is null then
      select l2_zoo_part_seq.nextval into :new.id from dual;
    end if;
  end;
/

CREATE or REPLACE TRIGGER l2_image_trg
before insert on l2_image
for each row
  begin
    if :new.id is null then
      select l2_image_seq.nextval into :new.id from dual;
    end if;
  end;
/

/*
 * Packages
 */
CREATE OR REPLACE PACKAGE insert_pkg AS

  PROCEDURE insert_staff_job(
    name in VARCHAR2,
    salary in NUMBER,
    id out number
  );

  PROCEDURE insert_staff(
    name in l2_name_type,
    job in NUMBER,
    id out NUMBER
  );

  PROCEDURE insert_aviary_staff(
    staff_id in VARCHAR2,
    aviary_id in VARCHAR2,
    id out NUMBER
  );

  PROCEDURE insert_aviary(
    type NUMBER,
    zoo_part NUMBER,
    id out NUMBER
  );

  PROCEDURE insert_aviary_type(
    name IN VARCHAR2,
    id OUT NUMBER
  );

  PROCEDURE  insert_zoo_part(
    name IN VARCHAR2,
    id OUT NUMBER
  );

  PROCEDURE insert_animal(
    type IN NUMBER,
    aviary IN NUMBER,
    id OUT NUMBER
  );

  PROCEDURE insert_food(
    animal_class in NUMBER,
    name in VARCHAR2,
    id OUT NUMBER
  );

  PROCEDURE insert_animal_class(
    name IN VARCHAR2,
    id out NUMBER
  );

  PROCEDURE insert_animal_type(
    name IN VARCHAR2,
    animal_class in NUMBER,
    id out NUMBER
  );

  PROCEDURE insert_image(
    photo in blob,
    id out NUMBER
  );

FUNCTION loadBlob(
    p_file_name VARCHAR2)
    RETURN BLOB;

END insert_pkg;

 CREATE OR REPLACE PACKAGE BODY insert_pkg AS

    PROCEDURE insert_staff_job(
      name in VARCHAR2,
      salary in NUMBER,
      id out number
    ) AS
      BEGIN
        INSERT INTO l2_staff_job(
          id,
          name,
          salary)
        VALUES(
          id,
          name,
          salary)
        returning id into id;

        commit;
      END;

    PROCEDURE insert_aviary_staff(
      staff_id in VARCHAR2,
      aviary_id in VARCHAR2,
      id out NUMBER
    ) AS
      BEGIN
        INSERT INTO l2_aviary_staff(
          id,
          staff_id,
          aviary_id)
        VALUES(
          id,
          staff_id,
          aviary_id)
        returning id into id;

        commit;
      END;

    PROCEDURE insert_staff(
      name in l2_name_type,
      job in NUMBER,
      id out NUMBER
    ) AS
      BEGIN
        INSERT INTO l2_staff(
          id,
          name,
          job)
        VALUES(
          id,
          name,
          job)
        returning id into id;

        commit;
      END;

    PROCEDURE insert_aviary(
      type NUMBER,
      zoo_part NUMBER,
      id out NUMBER
    ) AS
      BEGIN
        INSERT INTO l2_aviary(
          id,
          type,
          zoo_part)
        VALUES(
          id,
          type,
          zoo_part)
        returning id into id;

        commit;
      END;

     PROCEDURE insert_aviary_type(
      name IN VARCHAR2,
      id OUT NUMBER
    ) AS
      BEGIN
        INSERT INTO l2_aviary_type(
          id,
          name)
        VALUES(
          id,
          name)
        returning id into id;

        commit;
      END;

    PROCEDURE  insert_zoo_part(
      name IN VARCHAR2,
      id OUT NUMBER
    ) AS
      BEGIN
        INSERT INTO l2_zoo_part(
          id,
          name)
        VALUES(
          id,
          name)
        returning id into id;

        commit;
      END;

    PROCEDURE insert_animal(
      type IN NUMBER,
      aviary IN NUMBER,
      id OUT NUMBER
    ) AS
      BEGIN
        INSERT INTO l2_animal(
          id,
          type,
          aviary)
        VALUES(
          id,
          type,
          aviary
        )
        returning id into id;

        commit;
      END;

  PROCEDURE insert_food(
      animal_class in NUMBER,
      name in VARCHAR2,
      id OUT NUMBER
    ) AS
      BEGIN
        INSERT INTO l2_food(
          id,
          animal_class,
          name)
        VALUES(
          id,
          animal_class,
          name
        )
        returning id into id;

        commit;
      END;

     PROCEDURE insert_animal_class(
      name IN VARCHAR2,
      id out NUMBER
    ) AS
      BEGIN
        INSERT INTO l2_animal_class(
          id,
          name)
        VALUES(
          id,
          name
        )
        returning id into id;

        commit;
      END;

   PROCEDURE insert_animal_type(
      name IN VARCHAR2,
      animal_class in NUMBER,
      id out NUMBER
    ) AS
      BEGIN
        INSERT INTO l2_animal_type(
          id,
          animal_class,
          name)
        VALUES(
          id,
          animal_class,
          name
        )
        returning id into id;

        commit;
      END;

      PROCEDURE insert_image(
      photo IN blob,
      id out NUMBER
    ) AS
      BEGIN
        INSERT INTO l2_image(
          id,
          photo)
        VALUES(
          id,
          photo
        )
        returning id into id;

        commit;
      END;

    FUNCTION loadBlob(p_file_name VARCHAR2) RETURN BLOB AS
  dest_loc  BLOB := empty_blob();
  src_loc   BFILE := BFILENAME('TMT', p_file_name);
BEGIN
  -- Open source binary file from OS
  DBMS_LOB.OPEN(src_loc, DBMS_LOB.LOB_READONLY);

  -- Create temporary LOB object
  DBMS_LOB.CREATETEMPORARY(
        lob_loc => dest_loc
      , cache   => true
      , dur     => dbms_lob.session
  );

  -- Open temporary lob
  DBMS_LOB.OPEN(dest_loc, DBMS_LOB.LOB_READWRITE);


    -- Load binary file into temporary LOB
    DBMS_LOB.LOADFROMFILE(
        dest_lob => dest_loc
      , src_lob  => src_loc
      , amount   => DBMS_LOB.getLength(src_loc));

  exception
    when DBMS_LOB.operation_failed
    then
     return empty_blob();


 -- Close lob objects
  DBMS_LOB.CLOSE(dest_loc);
  DBMS_LOB.CLOSE(src_loc);

   -- Return temporary LOB object
  RETURN dest_loc;

END loadBlob;

  END insert_pkg;

/*
 * Insertion
 */

DECLARE
id NUMBER;
BEGIN
  INSERT_PKG.insert_zoo_part('north', id);
  INSERT_PKG.insert_zoo_part('central', id);
  INSERT_PKG.insert_zoo_part('west', id);

  insert_pkg.INSERT_AVIARY_TYPE('open', id);
  insert_pkg.INSERT_AVIARY_TYPE('cage', id);

  insert_pkg.insert_aviary(2,1,id); --cage north
  insert_pkg.insert_aviary(2,2,id); --cage central
  insert_pkg.insert_aviary(1,3,id); --open west

  insert_pkg.INSERT_STAFF_JOB('worker', '20000', id);
  insert_pkg.INSERT_STAFF_JOB('senior worker', '30000', id);


  insert_pkg.INSERT_ANIMAL_CLASS('predator',id);
  insert_pkg.INSERT_ANIMAL_CLASS('herbivorous',id);

  INSERT_PKG.insert_animal_type('lion',1, id);
  INSERT_PKG.insert_animal_type('tiger',1, id);
  INSERT_PKG.insert_animal_type('elephant',2, id);


  INSERT_PKG.insert_animal(1,1,id);
  INSERT_PKG.insert_animal(1,1,id);
  INSERT_PKG.insert_animal(1,1,id);

  INSERT_PKG.insert_animal(2,2,id);
  INSERT_PKG.insert_animal(2,2,id);

  INSERT_PKG.insert_animal(3,3,id);
  INSERT_PKG.insert_animal(3,3,id);
  INSERT_PKG.insert_animal(3,3,id);
  INSERT_PKG.insert_animal(3,3,id);

  INSERT_PKG.insert_food(1, 'meat', id);
  INSERT_PKG.insert_food(2, 'plant', id);

  INSERT_PKG.INSERT_STAFF(L2_NAME_TYPE('Yuriy','Borisovich','Sorokin'),1,id);
  INSERT_PKG.INSERT_STAFF(L2_NAME_TYPE('Alexey','Alexeevich','Pulich'),2,id);

  INSERT_PKG.INSERT_AVIARY_STAFF(1,1,id);
  INSERT_PKG.INSERT_AVIARY_STAFF(2,2,id);
  INSERT_PKG.INSERT_AVIARY_STAFF(2,3,id);

end;

/*
 * package
 */
CREATE OR REPLACE PACKAGE getData_pkg AS

  FUNCTION get_count_of_animals(stf_id in number) RETURN VARCHAR2;
  FUNCTION get_part_of_zoo_by_animals(anml_id in number) RETURN VARCHAR2;

END getData_pkg;

CREATE OR REPLACE PACKAGE BODY getData_pkg AS
  FUNCTION get_count_of_animals(stf_id in number)
    RETURN VARCHAR2 AS
    animal_count VARCHAR2(255) := ' ';
    BEGIN
      SELECT SUM(COUNT(*)) INTO animal_count FROM L2_ANIMAL INNER JOIN
        L2_AVIARY ON L2_ANIMAL.AVIARY = L2_AVIARY.ID INNER JOIN
        L2_AVIARY_STAFF ON L2_AVIARY.ID = L2_AVIARY_STAFF.AVIARY_ID INNER JOIN
        L2_STAFF ON L2_STAFF.ID = L2_AVIARY_STAFF.STAFF_ID
      WHERE L2_STAFF.ID = stf_id
      GROUP BY L2_animal.AVIARY;

      return animal_count;
    END;

FUNCTION get_part_of_zoo_by_animals(anml_id in number)
RETURN VARCHAR2 as
part VARCHAR2(255) := ' ';
BEGIN
SELECT ('animal n. ' || L2_ANIMAL.ID || ' in ' || L2_ZOO_PART.NAME || ' part') part into part FROM L2_ZOO_PART
INNER JOIN L2_AVIARY ON L2_AVIARY.ZOO_PART = L2_ZOO_PART.ID
INNER JOIN L2_ANIMAL ON L2_ANIMAL.AVIARY = L2_AVIARY.ID
WHERE L2_ANIMAL.ID = anml_id;
RETURN part;
End;
END getData_pkg;


