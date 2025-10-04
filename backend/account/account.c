#include "account.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sqlite3.h>
#include <string.h>

extern sqlite3 *db;

void createUser(const char* name, const char* fingerprintId) {
  char accountNumber[11];
  
  srand(time(NULL));

   for (int i = 0; i < 10; i++) {
      account_number[i] = '0' + rand() % 10;
  }
  account_number[10] = '\0';

  char sql[512];
  snprintf(sql, sizeof(sql),
      "INSERT INTO users(accountNumber, fingerprintId, name) "
        "VALUES('%s', '%s', '%s');",
        accountNumber, fingerprintId, name);
  
  char *err_msg = 0;
  int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
  if (rc != SQLITE_OK) {
      fprintf(stderr, "SQL error: %s\n", err_msg);
      sqlite3_free(err_msg);
  } else {
      printf("User created successfully!\nAccount Number: %s, Name: %s\n",
             accountNumber, name);
  }
}

int verifyPin(const char* pin) {
  char sql[256];
  sqlite3_stmt *stmt;
  int rc, result = 0;

 snprintf(sql, sizeof(sql),
             "SELECT COUNT(*) FROM users WHERE  pin = '%s';",
             accountNumber, pin);

 rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

 if(rc != SQLITE_OK) {
   fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    return 0;
 }

  rc = sqlite3_step(stmt);
  if (rc == SQLITE_ROW) {
      int count = sqlite3_column_int(stmt, 0);
      if (count == 1) {
          result = 1; // PIN is correct
      }
  }

  sqlite3_finalize(stmt);
  return result;

}
