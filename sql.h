#include <mysql/mysql.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

class Database {
  private:
    MYSQL * conn;
    const char * server; 
    const char * user;
    const char * password;
    const char * database;
    int id;
    char location[];

    int getID();
    int SendCount(int count);

  public:
    Database();
    ~Database();
};
//MYSQL * mysql_init();
//void count_in(MYSQL * conn, int);
//void count_out(int);
