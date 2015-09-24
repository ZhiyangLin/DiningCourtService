#include "sql.h"

Database::Database() {
  cout << "Database::Database()" << endl;

  // Store default database parameters
  server   = "mysql.ecn.purdue.edu";
  user     = "epics_dining";
  password = "raspberry";
  database = "epics_dining";

  // Connect to the MySQL database
  cout << "mysql_init" << endl;
  conn = mysql_init(NULL);
  cout << "mysql_real_connect" << endl;
  cout << "  Server:   " << server << endl;
  cout << "  Username: " << user << endl;
  cout << "  Password: " << password << endl;
  cout << "  Database: " << database << endl;

  if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
    cout << "Error connecting to the database:" << endl;
    cout << mysql_error(conn) << endl;
    exit(1);
  }

  // Get the camera's ID number
//  id = getID();

  // Ask the database for this camera's location
  SendCount(3);

  cout << "Successfully connected!" << endl;
}

Database::~Database() {
  cout << "Closing database connection" << endl;

  // Close the MySQL connection
  if (conn) mysql_close(conn);
}

int Database::getID() {
  /* Returns the ID number of this camera. If the camera does not have
   * an ID number then it asks the database to create a new entry.
   */

/*
  // Open up the configuration file to load in the ID number
  ifstream config; // File pointer for the config file
  string line;     // A string for storing a line that is read in

  cout << "Opening the config file" << endl;
  config.open("config");
  if (!config.is_open()) {
    cout << "The config file could not be opened!" << endl;
    exit(2);
  }
  cout << "config file opened" << endl;
  getline(config, line); // Read in the first line of the config file
  id = stoi(line); // Convert the first line into an integer
  cout << id << endl;
  config.close();
  cout << "config file closed" << endl;
*/
/*
  MYSQL_RES * result;
  unsigned int num_fields;
  unsigned int num_rows;
  if (mysql_query(conn, "SELECT * FROM Cameras")) {
    cout << "Query Failed" << endl;
    return -1; // Query failed
  }
  cout << "Query Success" << endl;

  result = mysql_store_result(conn);
  if (result) { // There are rows
    num_fields = mysql_num_fields(result);
    cout << num_fields << endl;
    mysql_free_result(result);
  } else { // mysql_store_result returned nothing
    cout << "No rows were returned" << endl;
    return -2;
  }


*/
}

int Database::SendCount(int count) {
  /*
   * Accepts an integer as the input. The integer is the count to send to the
   * database.
   *
   * Returns 0 for success, and a non-zero value for failure
   * Return Values:
   *  0: Success
   * -1: Query failed
   */

  MYSQL_RES * result;
  string str;// = "INSERT INTO EarhartEnter (Count) VALUES (1)";
  str = string("INSERT INTO ") + string("EarhartEnter") + string(" (Count) VALUES (") + to_string(count) + string(")");

  const char * query = str.c_str();
  if (mysql_query(conn, query)) {
    cout << "Query failed" << endl;
    return -1; // Query failed
  }
  cout << "Query success" << endl;


  return 0;
//  unsigned int field_count = mysql_field_count(conn); // Returns the number of columns for the most recent query on the connection

/*
  char location[]="EarhartEnter"; // This should be fetched from the database
  MYSQL * mysql_init() {
  //char server[]="maven.itap.purdue.edu";
  //char user[]="";
  //char password[]="";
  //char database[]="";
  MYSQL * conn = mysql_init(NULL);
  if(!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
    	fprintf(stderr, "?%s\n", mysql_error(conn));
      exit(1);
  }
  printf("db init\n");
  fflush(stdout);
*/
}

/*
void count_in(int people){
    char query[100];
    
    sprintf(query,"insert into %s (count) values(%d)",location, people);
    //printf("%d %s",people,query);
    fflush(stdout);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "!%s\n", mysql_error(conn));
        exit(1);
    }
}

void count_out(int people){
    
    char query[50];
    
    sprintf(query,"insert into %s (count) values(%d)",location, people);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "@%s\n", mysql_error(conn));
        exit(1);
    }
    
}

*/
