/*  Test file for the final phase of HY-340: Languages & Compilers
    Computer science dpt, University of Crete, Greece
*/

t = [ { "foo" : 0 } ];
t1 = [ "print", 34, 89, 100, true, false, nil ];

t[1453] = "this is a message";
t1[0]("this is a text message", "\n");	//run time error //nomizzw auto einai swsto!
t1[1](); //auto mallon einai lathos?
