<Query Kind="Expression" />

from line in new[] { "2 2 3", "2 7 9", "3 1 4", "2 13 20", "4 4 4", "3 10 12", "2 1 5", "4 20 30" }
select line.Split() into record
let r = int.Parse(record[0])
group new { c1 = long.Parse(record[1]),
            c2 = long.Parse(record[2]) + 1 } by r into rows
select from row in rows
       orderby row.c1
       select row