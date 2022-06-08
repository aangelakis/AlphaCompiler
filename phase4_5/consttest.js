table = [{
  "table1": [{ 1: (function(x) { print("table1_1 ", x); }) },
      { 2: (function(x) { print("table1_2 ", x); }) },
      { 3: (function(x) { print("table1_3 ", x); }) }
  ]
},
{
  "table2": [{ 1: (function(x) { print("table2_1 ", x); }) },
      { 2: (function(x) { print("table2_2 ", x); }) },
      { 3: (function(x) { print("table2_3 ", x); }) }
  ]
}
];

// table.table1[2]("ok1\n");
// table.table2[3]("ok2\n");

table["table1"][1](" == table 1_1\n");
table["table2"][1](" == table 2_1\n");
print(table);