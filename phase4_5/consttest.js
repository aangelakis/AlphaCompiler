vec3 = ["inside table"];
print(vec3[0]);  //works

vec3[0] = 55;
print(vec3[0]); //works

vec3[0] = nil;
print(vec3[0]); //works

vec3 = nil;   //crashes
print(vec3);
