function f() {}
tKey = [3];

t = [ 
	{ print : "print libFunc" }, 
	{ typeof : "typeof libFunc" }, 
	{ f : "f userFunc" }, 
	{ tKey : "tKey table" }, 
	{ true : "Trueeeeee" }, 
	{ "lala" : "lala string key" } 
];

print("must print >print libFunc<: ", t[print], "\n"); // print libFunc
print("must print >tKey table<: ", t[tKey], "\n"); // tKey table

t2 = tKey;
print("must print >tKey table<: ", t[t2], "\n"); // tKey table

t2 = [3];
print("must print nil or run time error: ", t[t2], "\n");


print("must print Trueeeee: ", t[true], "\n"); // Trueeee

func = f;
print("must print >f userFunc<: ", t[f], "\n"); // f userFunc
print("must print >f userFunc<: ", t[func], "\n"); // f userFunc

/*
We do not support functors!
*/
func = [
	{"()" : (function (t, msg){
		print("Call ", t.class, "'s print\n");
		print(msg);
	})},
	{"class": "Functor"}
];

func("LALA\n");
