PROGRAM alt(ctrl);
var shift : integer;
begin
	if shift < 0 then
		shift := shift + shift
	else
		shift := shift - shift
end
.
