//DONE
a1 = a2 = a3 = a4 = nil;

global_var = 0;

{
        local a1 = 2;
}

function foo() {
        ::global_var = 1;
}

//here global_var must be 1;
print(global_var, "\n");

function foo1(){
        local global_var = 2;
        //here (local) global_var must be 2
        print(global_var, "\n");
}

//here global_var must be 1
print(global_var, "\n");


global_var = global_var + 1;
global_var = global_var - 1;
global_var = global_var * 2;
global_var = global_var / 2;
global_var = global_var % global_var;

global_var = true;

if (not global_var)
        global_var = true;

else
        global_var = false;

for (i = 0; (i < 10 and global_var) or (i > 20); ++i) {
        i++;

        if( i != 1)
                print();

        if ( i <= 2) {
                i=9;
                print();
                i--;
                --i;
        }

        if (i == 1)
                ;

        else if (i >= 4)
                ;
        else
                continue;
}

while (not global_var) {

        if ( local j = not global_var)
                break;
}



object = [];

object = [1, 2, "test"];

object = [{"a":2}, {"b":2}, {"c":3}];


object..f();

object[0] = 2;
object["test"] = 2;
object.test = 2;

object = (function (){});

function test (){
        function test1(){
                return test;
        }
        return test1;
}

test();
test()();
test()()();



function test1 (){
        return [
                {"a":1},
                {"x" : [ {"y":[]}] }
        ];
}

test1().a = 2;
test1().test1f();
test1().test1f(1, 2);
print().a = 2;

print(a1.a2.a3.a4, "\n");

/*
x.y;
x..y();
*/
