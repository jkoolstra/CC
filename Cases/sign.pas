program sign(output);

var x, y, xy, xyz : integer;
var z : real;
var as : array [1 .. 3] of real;

begin
   as[2,3] := 25.3;
   x := 42;
   y := -1;
   xy := x*y;
   xyz := -1*x + (-xy);
   x := -x - x;
   z := as[2];
   writeln(z);
   readln(as[1],as[2]);
   writeln(as[1],as[2])
end.
