
create database studentDataBase;

create table User_info (
log_id varchar(100) not null unique,
password varchar(30) not null,
mode int default 0,
);

drop table Major;
alter table Student alter column log_id varchar(100);

create table Admin (
id int primary key,
log_id varchar(100) not null,
name varchar(30) not null,
foreign key (log_id) references User_info (log_id)
);

create table Student (
id int identity(1, 1) primary key,
log_id varchar(100) not null,
name varchar(30) not null,
class int not null,
foreign key (log_id) references User_info (log_id)
);

create table Stu_sch_rel (
id int primary key,
stu_id int,
school_id int,
type int,
foreign key (stu_id) references Student(id),
foreign key (school_id) references School(id)
);

create table Class (
id int primary key,
stu_id int not null,
foreign key (stu_id) references Student(id)
);

create table Grade (
id int primary key,
stu_id int,
chinese_grade int default 0,
math int default 0,
english int default 0,
overall int default 0,
foreign key (stu_id) references Student(id)
);

create table School (
id int primary key,
name varchar(30) not null,
);

create table Major (
id int identity(1, 1) primary key,
name varchar(100) not null,
school_id int,
score_info int,
foreign key (school_id) references School(id)
);




