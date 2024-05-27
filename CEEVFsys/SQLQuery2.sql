-- 插入用户数据
insert into User_info(log_id,stu_id, password, mode) values('student1','1', '123456', 0), 
('student2','2', '123456', 0);
insert into User_info(log_id, admin_id, password, mode) values('admin1', '1', '123456', 1);

select * from User_info;
-- 插入学生数据
insert into Student (log_id, class_id, score_id, stu_name) values('student1', '2202', 1000, 'frank'),
('student2', '2203', 1001, 'jack');
insert into Admin values('1001', 'admin1', 'tom');

truncate table Student;

select * from Student;

delete from Student where stu_id = 1002;

-- 插入班级数据
insert into Class values ('2202'), ('2203');

-- 插入学生成绩
insert into Grade (stu_id, chinese, math, english, overall) values(1000, 121, 135, 119, 245), ( 1001, 108, 114, 120, 239);
select * from Grade;
-- 插入学校信息
insert into School (school_name) values('RUC'), ('SEU'), ('DHU'), ('SISU')
, ('WUT'), ('CCNU'), ( 'JLU'), ( 'SJTU'), ('SCU');
select * from School;
select * from Major;

-- 插入专业信息
insert into Major (major_name) values ('Software Engineering'), ('Network Engineering'), ('Civil Engineering'), ('Environmental Engineering'),
('Architecture'), ('Material Science & Engineering'), ('Physics'), ('Chinese Language & Literature')
,('Pedagogy'), ('Physical Education'), ('English'), ('Journalism'), ('History')
,('Chemistry'), ('Biological Science'), ('Psychology'), ('Statistical Sciences'), ('Engineering Mechanics');

-- 插入学校专业关系
insert into Sch_may_rel (school_id, major_id, rel_sore) values (1000, 1000, 610), (1000, 1003, 595), (1000, 1006, 607),
(1000, 1007, 613), (1000, 1014, 585), (1000, 1017, 600), (1001, 1000, 622),
(1001, 1002, 602), (1001, 1005, 587), (1001, 1008, 599), (1001, 1015, 600),
(1002, 1000, 597), (1002, 1004, 583), (1002, 1007, 572), (1002, 1011, 602),
(1003, 1001, 605), (1003, 1003, 572), (1003, 1006, 579), (1003, 1011, 593),
(1004, 1001, 624), (1004, 1003, 598), (1004, 1009, 601), (1004, 1015, 583),
(1005, 1003, 587), (1005, 1004, 573), (1005, 1008, 563), (1006, 1013, 585),
(1006, 1002, 601), (1006, 1005, 611), (1006, 1009, 631), (1006, 1016, 618),
(1007, 1000, 612), (1007, 1003, 597), (1007, 1006, 621), (1007, 1010, 593),
(1008, 1000, 555), (1008, 1002, 569), (1008, 1014, 573), (1008, 1015, 570);

-- 插入学生志愿
insert into Stu_vul (stu_id, school_id, major_id) values (1000, 1000, 1000), (1000, 1000, 1017), (1000, 1003, 1001),
(1000, 1005, 1004), (1000, 1007, 1006), (1000, 1008, 1015), (1001, 1000, 1006), (1001, 1000, 1017), (1001, 1002, 1000),
(1001, 1004, 1003), (1001, 1006, 1009), (1001, 1007, 1010);

truncate table Stu_vul; 

select * from Stu_vul;
-- 登录过程 log
create procedure Login	
@sno varchar(100),@pw varchar(30)
as
select COUNT(*) as cnt from User_info
where log_id=@sno and password=@pw;

drop procedure Login;
-- 查找模式 log
create procedure Find_mode
@sno char(100)
as
select mode from User_info
where log_id = @sno;

select mode from User_info where log_id = 'student1';
select * from User_info where log_id = 'student1';
drop procedure Login;

-- 学生系统信息过程 stu
create procedure Stud
@sno varchar(100)
as
select * from Student
where log_id=@sno;

drop procedure Scla;

-- 查询学生成绩过程 stu
create procedure Scla
@sno bigint
as
select chinese, math, english, overall, (chinese + math + english + overall) as sum
from Grade
where stu_id = @sno;

drop procedure Scla;

-- 查询各个学校录取最低分 stu
CREATE PROCEDURE Find_sch
AS
BEGIN
    SELECT 
		s.school_id as sch_id,
        s.school_name AS sch_name, 
        MIN(sr.rel_sore) AS min_score
    FROM 
        School s
    JOIN 
        Sch_may_rel sr ON s.school_id = sr.school_id
    JOIN 
        Major m ON sr.major_id = m.major_id
    GROUP BY 
        s.school_name, s.school_id;
END;

drop procedure Find_sch;

-- 查询学校号 stu
create procedure Find_sch_id
@m_sch_name varchar(100)
as 
select School.school_id as id
from School
where School.school_name = @m_sch_name;

drop procedure Find_sch_id;

-- 查询专业
create procedure Find_may_id
@may_name varchar(100)
as
select Major.major_id as id
from Major
where Major.major_name = @may_name;

-- 查询学校专业 stu
create procedure Find_sch_may
@m_sch_id int
as 
select Major.major_id as id, Major.major_name as major_name, Sch_may_rel.rel_sore as rel_soce
from Major, Sch_may_rel
where Sch_may_rel.school_id = @m_sch_id and Sch_may_rel.major_id = Major.major_id;

drop procedure Find_sch_may;

-- 查询学生志愿 stu
create procedure Find_stu_vul
@m_id bigint
as
select distinct School.school_name as sch, Major.major_name as may
from Student, School, Major, Stu_vul
where Stu_vul.stu_id = @m_id and Stu_vul.school_id = School.school_id and Stu_vul.major_id = Major.major_id;

drop procedure Find_stu_vul;


-- 检查学校号是否存在 stu
create procedure check_sch
@stu_id int
as
select COUNT(*) as cnt from School
where School.school_id = @stu_id;

-- 检查专业号是否存在 stu
create procedure check_may
@may_id int
as
select COUNT(*) as cnt from Major
where Major.major_id = @may_id;

-- 检查志愿是否重复 stu
create procedure check_dup
@stu_id int, @sch_id int, @may_id int
as 
select count(*) as cnt from Stu_vul
where Stu_vul.stu_id = @stu_id and Stu_vul.school_id = @sch_id and Stu_vul.major_id = @may_id;


-- 插入学生志愿 stu
create procedure add_stu_vul
@m_stu_id int, @m_sch_id int, @m_may_id int
as 
insert into Stu_vul(stu_id, school_id, major_id)
values (@m_stu_id, @m_sch_id, @m_may_id);

-- 删除学生志愿 stu
create procedure del_stu_vul
@m_stu_id int, @m_sch_id int, @m_may_id int
as 
delete from Stu_vul
where @m_stu_id = Stu_vul.stu_id and @m_sch_id = Stu_vul.school_id and @m_may_id = Stu_vul.major_id;

delete from Stu_vul
where 1000 = Stu_vul.stu_id and 1005 = Stu_vul.school_id and 1008 = Stu_vul.major_id;

select * from Stu_vul;

-- 查询学校和专业 admin
create procedure Find_admin_sch_may
as
select distinct sm.school_id as sch_id, s.school_name as sch_name, sm.major_id as m_id, m.major_name as m_name, sm.rel_sore as score
from Sch_may_rel sm, School s, Major m
where sm.school_id = s.school_id and sm.major_id = m.major_id;

drop procedure Find_admin_sch_may;

-- 查询所有学生信息
create procedure Find_all_stu
as
select s.stu_id as id, s.stu_name as name, s.class_id as class, (g.chinese + g.english + g.math + g.overall) as score
from Student s , Grade g
where s.score_id = g.score_id;

-- 插入学校
create procedure Insert_sch
@sch_name varchar(100)
as
insert into School values(@sch_name);

-- 插入专业
create procedure Insert_may
@may_name varchar(100)
as
insert into Major values(@may_name);

-- 插入学校专业
create procedure Insert_sm_rel
@sch_id int, @may_id int, @score int
as
insert into Sch_may_rel values(@sch_id, @may_id, @score);

-- 删除rel学校信息
create procedure Del_s_rel
@sch_id int
as 
delete from Sch_may_rel 
where Sch_may_rel.school_id = @sch_id;

-- 删除学校
create procedure Del_sch
@sch_name varchar(100)
as 
delete from School 
where School.school_name = @sch_name;

-- 删除rel专业
create procedure Del_m_rel
@may_id int
as 
delete from Sch_may_rel 
where Sch_may_rel.major_id = @may_id;

-- 删除专业
create procedure Del_may
@may_name varchar(100)
as
delete from Major
where Major.major_name = @may_name;


CREATE PROCEDURE Find_score
    @m_class INT, 
    @m_cou VARCHAR(100)
AS
BEGIN
    DECLARE @sql NVARCHAR(MAX);

    -- Construct the dynamic SQL query
    SET @sql = N'
        SELECT 
            MAX(g.' + QUOTENAME(@m_cou) + N') AS Highest_Score,
            MIN(g.' + QUOTENAME(@m_cou) + N') AS Lowest_Score,
            AVG(g.' + QUOTENAME(@m_cou) + N') AS Average_Score
        FROM 
            Student s
        JOIN 
            Grade g ON s.score_id = g.score_id
        WHERE 
            s.class_id = @m_class;
    ';

    -- Execute the dynamic SQL query
    EXEC sp_executesql @sql, N'@m_class INT', @m_class;
END;



