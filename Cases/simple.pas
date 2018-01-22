PROGRAM alt(ctrl);
var x, y : integer;
var z : real;
var as : array [1 .. 3] of integer;
begin
	x := 1;
	y := 3.14;
	if(x >= y) then
		x:= 0
	else
		x := 1;
	y := x - 2 * y;
	as[x,2,3] := 1;
	z := as[x];
	writeln(1, z);
	readln(z);
	writeln(z)
end
.
