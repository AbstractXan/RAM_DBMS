# RAM_DBMS
RAM based DBMS implemented in C++

# Current Features

### Create Table

Given table name, number of columns and column description, the DBMS will create a table in the database with the constraints given to it.

### Insert into Table

Given a tuple and table name, it inserts the data into the table after checking for duplicate keys.

### Delete from Table

Given the tablename, it will delete rows from the table which satisfy the given where condition.
If no where condition is given, then all the tuples in the table will get deleted.

### Select from Table

Given the columnnames and the tablename, the DBMS will show all the tuples for the columnnames provided in the query in the table which satisfy the where condition provided by the user.
If no condition is provided, the all the tuples for the particular columnnames from the table are displayed.
If '*' is entered instead of the columnnames, then the whole table will be displayed.
