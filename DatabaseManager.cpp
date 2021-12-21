#include <iostream>
#include <stdio.h> 
#include <sqlite3.h>
#include <string>

using namespace std;

/*
class DatabaseManager {

	public:

		int createDB(const char* s);
		int createTable(const char* s);
		int insertData(const char* s);
		int selectData(const char* s);
		static int callback(void* NotUsed, int argc, char** argv, char** azColName);
		int updateData(const char* s);
		int deleteData(const char* s);

};
*/

int createDB(const char* s)
{
    sqlite3* DB;
    int exit = 0;

    exit = sqlite3_open(s, &DB);

    sqlite3_close(DB);

    return 0;
}

int createTable(const char* s)
{
    sqlite3* DB;

    string sql = "CREATE TABLE IF NOT EXISTS ACCOUNT("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "FNAME TEXT NOT NULL, "
        "MNAME TEXT NOT NULL, "
        "LNAME TEXT NOT NULL, "
        "BIRTHDAY INTEGER NOT NULL, "
        "ADDRESS TEXT NOT NULL, "
        "TYPEOFID TEXT NOT NULL, "
        "IDNUMBER TEXT NOT NULL, "
        "ACCOUNTSTATUS TEXT NOT NULL, "
        "PINNUMBER TEXT NOT NULL);";

    try {
        int exit = 0;
        exit = sqlite3_open(s, &DB);

        char* messaggeError;
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

        if (exit != SQLITE_OK) {
            cerr << "Error Create Table" << endl;
            sqlite3_free(messaggeError);
        }
        else
            cout << "Table created successfully" << endl;
        sqlite3_close(DB);
    }
    catch (const exception& e)
    {
        cerr << e.what();
    }

    return 0;
}

int insertData(const char* s)
{

    sqlite3* DB;
    char* messageError;

    int exit = sqlite3_open(s, &DB);

    string sql("INSERT INTO GRADES (NAME, LNAME, AGE, ADDRESS, GRADE) VALUES('Alice', 'Chapa' , 35, 'Tampa', 'A' );"
        "INSERT INTO GRADES (NAME, LNAME, AGE, ADDRESS, GRADE) VALUES('Angelo', 'Dionisio' , 19, 'Malimatoc 2, Mabini, Batangas', 'B' );"
        "INSERT INTO GRADES (NAME, LNAME, AGE, ADDRESS, GRADE) VALUES('France', 'Cooper' , 24, 'New York', 'c' );");

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cerr << "Error Insert" << endl;
        sqlite3_free(messageError);
    }
    else
        cout << "REcords created successfully!" << endl;

    return 0;
}

int selectData(const char* s)
{
    sqlite3* DB;

    int exit = sqlite3_open(s, &DB);
    string sql = "SELECT * FROM GRADES;";

    /* aN OPEN DATABSE , SQL TO BE evaluated, callback function, 1st argument to callback, error meg will be written here*/
    sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);

    return 0;
}


// retrieve the contents of the database used by selectdata()
/* argc: holds the number of results, azcolname: hold each column returned in array,argv: hols each value in array */
int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
    for (int i = 0; i < argc; i++) {
        //column name and value 
        std::cout << azColName[i] << ": " << argv[i] << endl;
    }

    cout << endl;

    return 0;


}

int updateData(const char* s)
{
    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open(s, &DB);

    string sql("UPDATE GRADES SET GRADE = 'A' WHERE LNAME = 'Cooper'");
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
        cerr << "Error Update" << endl;
        sqlite3_free(messaggeError);
    }
    else
        cout << "REcords updated successfully!" << endl;

    return 0;
}

int deleteData(const char* s)
{
    sqlite3* DB;

    int exit = sqlite3_open(s, &DB);
    string sql = "DELETE FROM GRADES;";
    sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);
    return 0;
}




