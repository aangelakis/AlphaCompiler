vec1 = [1, 2, 3];

t = [{"e" : "fae skata aleks"}, {"f" : 69}, {"peos":vec1}];

print(objecttotalmembers(t));
print("\n");

print(typeof(t));
print("\n");
print(t);
print("\n");

t2 = objectcopy(t);

print(t2);
print("\n");

t["e"] = nil;
t2["f"] = nil;
t2["peos"][0] = nil;
t2["peos"][1] = nil;

print(t);
print("\n");
print(t2);
print("\n");