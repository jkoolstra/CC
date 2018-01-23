


PROGRAM test(input, output);
_1 : array [1 .. 10] of integer ; _3, _4 : real ; _5 : array [1 .. 17] of real ;

FUNCTION test1(a, b : integer ; c, d : real ; e : array [1 .. 10] of integer) : integer;
BEGIN
    testWHAT; { ERROR: no "testWHAT" procedure declared. }
    e := 5; { ERROR: assigning array. }
    e := e; { ERROR: assigning array. }
    _1[2] = _5[16]; { WARNING: implicit cast of real to integer . }
    f[5] = 10; { ERROR: variable "f" not declared before use.  }
    a[5] := 7; { ERROR: "a" is not an array }

    a = 7; { Should be OK I think! }

    test1(a, b, c, d, e); { Should be OK I think! }

    test1 := 5.8; { WARNING: implicit cast of real to integer. }
    test1 := test1; { ERROR: "test1" is not a variable }

    test1 := test1(a, b, c, d, e); { Should be OK I think! }

END;

BEGIN
    test1(_1, _2); { ERROR: function "test1" called with 2 arguments, expected 5 arguments. }
    test1(_1[0], _1[1], _3, _4, _1[2]); { ERROR: expected parameter 5 of function call to
                                          "test1" to be of type "array of integer", but found
                                          type "integer". }
    test1(_1[0], _1[1], _3, _4, _5); { ERROR: expected parameter 5 of function call to
                                       "test1" to be of type "array of integer", but found
                                       type "array of real". }

    test1(_1[0], _1[1], _3, _4, _1); { Should be OK I think! }
END.
