drop table studentenrolledcourses;
drop table my_tmp;

drop table section cascade constraints;
drop table clientsession cascade constraints;
drop table myclient cascade constraints;
drop table student cascade constraints;
drop table class cascade constraints;
drop table prereq cascade constraints;


create table myclient (
	clientid varchar2(8) primary key,
	password varchar2(12),
	aflag varchar2(1),
	sflag varchar2(1)
);

create table clientsession (
	sessionid varchar2(32) primary key,
	clientid varchar2(8) not null,
	sessiondate date,
	foreign key (clientid) references myclient ON DELETE CASCADE
);

create table student (
	sid varchar2(8) primary key,
	fname varchar2(30) not null,
	lname varchar2(30) not null,
	clientid varchar2(8) not null,
	age number(2),
	streetNumber number(8),
	streetName varchar2(30),
	city varchar2(30),
	state varchar2(30),
	zipCode varchar2(6),
	typeflag varchar2(13) , 
	probationflag varchar2(13),
	concentration varchar2(32),
	gpa number(2,1),
	foreign key (clientid) references myclient ON DELETE CASCADE
);

create table class (
	cid varchar2(8) primary key,
	title varchar2(30),
	credits number(1)
); 

create table section (
	cid varchar2(8) not null,
	sectionid number(4) unique not null,
	yr number(4) not null,
	season varchar2(6) not null,
	stime varchar2(10),
	maxstudents number(3),
	numstudents number(3),
	enrolldeadline date,
	primary key (cid, sectionid, yr, season),
	foreign key (cid) references class
);

create table studentenrolledcourses (
	sid varchar2(8) not null,
	cid varchar2(8) not null,
	yr number(4) not null,
	season varchar2(6) not null,
	sectionid number(4) not null,
	enrollflag varchar2(1),
	grade number(1),
	primary key (sid, cid, sectionid, yr, season),
	foreign key (sid) references student ON DELETE CASCADE,
	foreign key (cid, sectionid, yr, season) references section (cid, sectionid, yr, season)
);

create table prereq (
    cid varchar2(8) not null,
	prereqcid varchar2(8) not null,
	primary key (cid, prereqcid),
	foreign key (cid) references class,
	foreign key (prereqcid) references class
);

create table my_tmp(
	my_grade number,
	my_credits number
);

--probationflag trigger
create or replace trigger probation_trigger
	after insert or update of gpa on Student
	declare
		CURSOR c1 is select sid, gpa from student order by sid;
		my_sid varchar2(8);
		my_gpa number(2,1);
	begin
		OPEN c1;
		LOOP
			fetch c1 into my_sid, my_gpa;
			EXIT WHEN c1%NOTFOUND;
			IF my_gpa < 2.0 THEN
				update student set probationflag = 1 where sid = my_sid;
			ELSE
				update student set probationflag = 0 where sid = my_sid;
			END IF;
		END LOOP;
		CLOSE c1;
	end;
	/

--update_gpa procedure
create or replace procedure update_gpa(student_id in varchar2) as
	CURSOR c1 is select grade, credits from class natural join studentenrolledcourses
	where sid = student_id and grade > -1;

	my_grade number;
	my_credits number;

	grade_total number;
	credits_total number;

	my_gpa number(3,1);
	begin

		delete from my_tmp;
		commit;
		
		open c1;
		LOOP
			fetch c1 into my_grade, my_credits;
			EXIT WHEN c1%NOTFOUND;
			my_grade := my_grade * my_credits;
			insert into my_tmp values(my_grade, my_credits);
			commit;
		END LOOP;
		close c1;
		select SUM(my_grade) into grade_total from my_tmp;
		select SUM(my_credits) into  credits_total from my_tmp;
		my_gpa := grade_total/credits_total;
		update student set gpa = my_gpa where sid = student_id;
		commit;
	end;
	/

-- Student Update Procedure
CREATE OR REPLACE PROCEDURE update_student_info(
	client_id IN VARCHAR2,
    s_id IN VARCHAR2,
	f_name VARCHAR2,
    l_name IN VARCHAR2,
    pass_word IN VARCHAR2,
    a_flag IN VARCHAR2,
    s_flag IN VARCHAR2,
    agen IN NUMBER,
    street_number IN NUMBER,
    street_name IN VARCHAR2,
	new_city IN VARCHAR2,
	st IN VARCHAR2,
	zip IN VARCHAR2,
	type_flag IN VARCHAR2,
	probation_flag IN VARCHAR2	
	) AS

BEGIN
	-- Update myclient
	UPDATE myclient 
	SET aflag = a_flag, sflag = s_flag, clientid = client_id 
	WHERE clientid = client_id;
	-- Update student
	UPDATE student
	SET sid=sid, fname=f_name, lname=l_name, age=agen, streetNumber=street_number, streetName=street_name
	, city=new_city, state=st, zipCode=zip, typeflag=type_flag, probationflag=probation_flag
	WHERE sid=s_id;
	COMMIT;
		
END update_student_info;
/

CREATE OR REPLACE PROCEDURE enroll_student (
    my_sid IN VARCHAR2,
    my_cid IN VARCHAR2,
    my_sectionid IN NUMBER,
    my_yr IN NUMBER,
    my_season IN VARCHAR2,
    my_error OUT VARCHAR2
) AS
    my_students NUMBER;
    my_max_students NUMBER;
	cur_enroll NUMBER;
	max_enroll NUMBER;
    pqs_needed NUMBER;
	pqs_done NUMBER;
	seats_open NUMBER;
    my_enroll_deadline DATE;
BEGIN
    -- Exist Check
    SELECT COUNT(*) INTO my_students
    FROM section
    WHERE cid = my_cid AND sectionid = my_sectionid AND yr = my_yr AND season = my_season;
    IF my_students = 0 THEN
        my_error := 'Section ' || my_sectionid || ' no longer exists for the ' || my_yr || ' ' || my_season || ' term';
        RETURN;
    END IF;

    -- Deadline Check
    SELECT enrolldeadline INTO my_enroll_deadline
    FROM section
    WHERE cid = my_cid AND sectionid = my_sectionid AND yr = my_yr AND season = my_season;

    IF my_enroll_deadline < SYSDATE THEN
        my_error := 'Enrollment deadline has passed for  ' || my_cid ||  ' during the  ' || my_yr || ' '|| my_season|| ' term ';
        RETURN;
    END IF;

    -- Currently Enrolled Check
    SELECT COUNT(*) INTO my_students
    FROM studentenrolledcourses
    WHERE sid=my_sid AND cid=my_cid AND sectionid=my_sectionid AND yr=my_yr AND season=my_season AND enrollflag = 1;
    IF my_students > 0 THEN
        my_error := 'Student is already enrolled in course for this term ';
        RETURN;
    END IF;

    -- Prereq Check
    SELECT COUNT(*) INTO pqs_needed FROM prereq WHERE cid = my_cid;
    SELECT COUNT(*) INTO pqs_done FROM studentenrolledcourses 
	WHERE sid=my_sid
	 AND grade>1 
	 AND enrollflag=0 
	 AND cid IN (SELECT prereqcid FROM prereq WHERE cid = my_cid);
	IF pqs_needed <> pqs_done THEN
        my_error := 'STUDENT HAS NOT MET ALL PREREQUISITES TO ENROLL IN ' || my_cid;
        RETURN;
    END IF;	

    -- Section Size Check and Enrollment
	SELECT numstudents, maxstudents INTO cur_enroll, max_enroll FROM section
	WHERE cid=my_cid 
	AND sectionid=my_sectionid 
	AND yr=my_yr 
	AND season=my_season;

	IF max_enroll - cur_enroll > 0 THEN
        INSERT INTO studentenrolledcourses (sid, cid, sectionid, yr, season, enrollflag)
        VALUES (my_sid, my_cid, my_sectionid, my_yr, my_season, 1);
        UPDATE section
        SET numstudents = numstudents + 1
        WHERE cid = my_cid AND sectionid = my_sectionid AND yr = my_yr AND season = my_season;
        COMMIT;	
	ELSE
        my_error := 'Section' || my_sectionid || ' is FULL ';
    END IF;
	
EXCEPTION
    WHEN OTHERS THEN
        -- Error Occured
        ROLLBACK;
        my_error := SQLERRM;
END enroll_student;
/

create or replace procedure new_student_id
	(my_fname in varchar2, my_lname in varchar2, my_clientid in varchar2, my_sid out varchar2, my_error out varchar2)
	is
	my_count number;
	begin
		LOCK TABLE student in ROW EXCLUSIVE MODE NOWAIT;
		select count(*) into my_count from student;
		my_count := my_count + 1;
		my_sid := SUBSTR(my_fname,1,1) || SUBSTR(my_lname,1,1)
			|| TO_CHAR(my_count,'FM000000');
		insert into student (sid, fname, lname, clientid) values (my_sid, my_fname, my_lname, my_clientid); 
		commit;
		my_error := my_sid;
	end;
	/

create or replace view currently_enrolled_courses as
	select sid, cid, title, sectionid, credits, grade
	from class natural join studentenrolledcourses where enrollflag = 1;


insert into myclient values ('mthomas', 'mthomas', 0, 1);
insert into myclient values ('pgeorge', 'pgeorge', 1, 1);
insert into myclient values ('jdoe', 'jdoe', 0, 1);

insert into myclient values ('cprather', 'cprather', 0, 1);
insert into myclient values ('jswanson', 'jswanson', 0, 1);
insert into myclient values ('rdaniels', 'rdaniels', 1, 0);

insert into myclient values ('username', 'password', 0, 1);
INSERT INTO myclient VALUES ('user1', 'password1', '0', '1');
INSERT INTO myclient VALUES ('user2', 'password2', '0', '1');




insert into student values ('pg000001', 'Paul', 'George', 'pgeorge', 25, 462, 'South Ave', 'Edmond', 'OK', '73013', 'u', 0, null, null);
insert into student values ('mt000002', 'Mike', 'Thomas', 'mthomas', 25, 293, '2nd St' , 'Edmond', 'OK', '73014', 'g', 0, null, null);
insert into student values ('jd000003', 'John', 'Doe', 'jdoe', 25, 849, 'Washington St', 'Edmond', 'OK', '74051', 'u', 0, null, null);

insert into student values ('cp000004', 'Cole', 'Prather', 'cprather', 20, 435, 'Redbud St', 'Norman', 'OK', '73072', 'u', 0, null, null);
insert into student values ('js000005', 'Joe', 'Swanson', 'jswanson', 40, 3737, 'Feather Cir', 'Edmond', 'OK', '73013', 'u', 0, null, null);



insert into class values ( 'CMSC1111', 'Intro to Computers', 3);
insert into class values ( 'CMSC2111', 'Programming 1', 3);
insert into class values ( 'CMSC3111', 'Programming 2', 3);
insert into class values ( 'CMSC4111', 'Databases', 4);

insert into class values ( 'MATH1111', 'Math 1', 4);
insert into class values ( 'MATH2111', 'Math 2', 4);
insert into class values ( 'MATH3111', 'Math 3', 4);
insert into class values ( 'MATH4111', 'Math 4', 4);

insert into class values ( 'HLTH1111', 'Health 1', 1);
insert into class values ( 'HIST4111', 'US History', 2);
insert into class values ( 'ECON3111', 'Economics', 3);
insert into class values ( 'PHYS4111', 'Physics', 4);

insert into prereq values ( 'CMSC2111', 'CMSC1111');
insert into prereq values ( 'CMSC3111', 'CMSC2111');
insert into prereq values ( 'CMSC4111', 'CMSC3111');
insert into prereq values ( 'CMSC4111', 'MATH2111');
insert into prereq values ( 'MATH2111', 'MATH1111');
insert into prereq values ( 'MATH3111', 'MATH2111');
insert into prereq values ( 'MATH4111', 'MATH3111');
insert into prereq values ( 'PHYS4111', 'MATH2111');



insert into section values ('CMSC1111', 0001, 2023, 'Fall',    0,  3, 3, TO_DATE('20230815', 'yyyymmdd'));
insert into section values ('CMSC1111', 0002, 2024, 'Spring',    0,  3, 3, TO_DATE('20250101', 'yyyymmdd'));
insert into section values ('CMSC2111', 0003, 2024, 'Spring',   0,  2, 1, TO_DATE('20250101', 'yyyymmdd'));
insert into section values ('CMSC3111', 0004, 2024, 'Spring',   0,  2, 0, TO_DATE('20250101', 'yyyymmdd'));
insert into section values ('CMSC4111', 0005, 2024, 'Spring',   0,  2, 0, TO_DATE('20250101', 'yyyymmdd'));
insert into section values ('CMSC1111', 0006, 2024, 'Fall', 1300,  3, 0, TO_DATE('20251225', 'yyyymmdd'));
insert into section values ('CMSC2111', 0007, 2024, 'Fall', 1400,  2, 0, TO_DATE('20251101', 'yyyymmdd'));
insert into section values ('CMSC3111', 0008, 2024, 'Fall', 1500,  1, 0, TO_DATE('20251225', 'yyyymmdd'));
insert into section values ('CMSC4111', 0009, 2024, 'Fall', 1700,  1, 0, TO_DATE('20251225', 'yyyymmdd'));

insert into section values ('MATH1111', 0010, 2023, 'Fall',    0,  3, 3, TO_DATE('20230815', 'yyyymmdd'));
insert into section values ('MATH1111', 0011, 2024, 'Spring',    0,  3, 3, TO_DATE('20250101', 'yyyymmdd'));
insert into section values ('MATH2111', 0012, 2024, 'Spring',    0,  2, 1, TO_DATE('20250101', 'yyyymmdd'));
insert into section values ('MATH3111', 0013, 2024, 'Spring',   0,  2, 0, TO_DATE('20240101', 'yyyymmdd'));
insert into section values ('MATH1111', 0014, 2024, 'Fall', 1300,  3, 0, TO_DATE('20251225', 'yyyymmdd'));
insert into section values ('MATH2111', 0015, 2024, 'Fall', 1400,  2, 0, TO_DATE('20251101', 'yyyymmdd')); 
insert into section values ('MATH3111', 0016, 2024, 'Fall', 1500,  2, 0, TO_DATE('20251225', 'yyyymmdd'));
insert into section values ('MATH4111', 0017, 2024, 'Fall', 1200,  1, 0, TO_DATE('20251225', 'yyyymmdd'));

insert into section values ('HLTH1111', 0018, 2024, 'Spring', 1200, 10, 0, TO_DATE('20250101', 'yyyymmdd'));
insert into section values ('HIST4111', 0019, 2024, 'Spring', 0, 5, 0, TO_DATE('20250101', 'yyyymmdd'));
insert into section values ('ECON3111', 0020, 2024, 'Spring', 1000, 3, 0, TO_DATE('20250101', 'yyyymmdd'));
insert into section values ('PHYS4111', 0021, 2024, 'Spring', 1300, 2, 0, TO_DATE('20250101', 'yyyymmdd'));
insert into section values ('HLTH1111', 0022, 2023, 'Spring', 1200, 10, 0, TO_DATE('20230101', 'yyyymmdd'));
insert into section values ('HIST4111', 0023, 2023, 'Spring', 0, 5, 0, TO_DATE('20230101', 'yyyymmdd'));
insert into section values ('ECON3111', 0024, 2023, 'Spring', 1000, 3, 0, TO_DATE('20230101', 'yyyymmdd'));
insert into section values ('PHYS4111', 0025, 2023, 'Spring', 1300, 2, 0, TO_DATE('20230101', 'yyyymmdd'));

insert into studentenrolledcourses values ( 'pg000001', 'CMSC1111', 2024, 'Spring', 0002, 1, 0);
insert into studentenrolledcourses values ( 'jd000003', 'CMSC1111', 2024, 'Spring',0002, 0, 0);
insert into studentenrolledcourses values ( 'mt000002', 'CMSC1111', 2023, 'Fall', 0001, 0, 4);
insert into studentenrolledcourses values ( 'mt000002', 'CMSC2111', 2024, 'Spring',0003, 1, 0);
insert into studentenrolledcourses values ( 'mt000002', 'MATH1111', 2024, 'Spring',0011, 0, 1);

insert into studentenrolledcourses values ( 'js000005', 'MATH1111', 2023, 'Fall' ,0010, 1, 0);
insert into studentenrolledcourses values ( 'js000005', 'CMSC1111', 2024, 'Spring',0002, 1, 0);
insert into studentenrolledcourses values ( 'js000005', 'MATH2111', 2024, 'Spring',0012, 1, 0);
insert into studentenrolledcourses values ( 'cp000004', 'CMSC1111', 2024, 'Spring',0002, 1, 0);
insert into studentenrolledcourses values ( 'cp000004', 'MATH1111', 2024, 'Spring',0011, 1, 0);

commit;