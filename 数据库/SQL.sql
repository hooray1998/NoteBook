
2.1
select S.Sno, S.Sname from S,SC where SC.Cno = '1' and SC.Sno = S.Sno;

2.2
select S.Sno, S.Sname from S,C,SC where C.Cname = '数据结构' and SC.Sno = S.Sno and SC.Cno = C.Cno;

2.3

select Sno, Sname from S where not exists (
	select * from SC where SC.Sno = S.Sno and SC.Cno = '1'
);

2.4
select Sname from S where not exists (
	select * from C where not exists (
		select * from SC where S.Sno = SC.Sno and SC.Cno = C.Cno
	)
);

2.5 !!!!!!有问题
select S.Sno, AVG(X.Grade) g from S,SC X where not exists (
	select * from SC Y where Y.Sno=S.Sno and Y.Grade<60 and Y.Cno!='1'
) S.Sno = X.Sno and group by Sno order by g DESC;

select S.Sno, AVG(SC.Grade) from S,SC where SC.Cno != '1' and SC.Sno = S.Sno;



2.6
select S.Sname from S,C,SC where C.Cname = '数据库原理' and SC.Sno = S.Sno and SC.Cno = C.Cno order by SC.Grade limit 1,1;

2.7
select S.Sname,C.Cname from S,C,SC where C.Ccredit=3 and SC.Grade>=80 and SC.Sno = S.Sno and SC.Cno = C.Cno group by S.Sname;
select S.Sname from S,C,SC where C.Ccredit=3 and SC.Grade>=80 and SC.Sno = S.Sno and SC.Cno = C.Cno group by S.Sname having count(*)>=3;

2.8
方法一:
select Sno from (select Sno, count(*) from SC group by Sno) as SC_Count(Sno, Cnt) 
group by Cnt
having count(*) = 1;
方法二:
create view SC_Count_view(Sno, Cnt)
select Sno, count(*) from SC group by Sno;

select Sno from SC_Count_view X where not exists (select * from SC_Count_view Y where X.Cnt = Y.Cnt and X.Sno!=Y.Sno );

2.9


实验三

3.1
update SC
set Grade=Grade*1.1
where Cno='1' and Grade!=NULL

3.2
delete from SC
where Cno=(
	select Cno from C where Cname='数据结构'
);

3.3
delete from S where Sno='201215122';
delete from SC where Sno='201215122';

实验四
4.1
create view Man
select S.Sno, Sname, C.Cname, SC.Grade from S,C,SC where S.Ssex='男' and S.Sno=SC.Sno and SC.Cno=C.Cno;

4.2
select Sno, Sname from Man group by Sno having AVG(Grade)>80;


实验五
5.1
select Sno,COUNT(*),AVG(Grade) from SC group by Sno;

5.2
grant all privileges
on table S,C,SC
to public;

5.3
drop table S,C,SC;
