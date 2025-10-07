#include "account.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sqlite3.h>
#include <string.h>

extern sqlite3 *db;

void createUser(const char* name, const char* fingerprintId, double balance) {
  char accountNumber[11];
  
  srand(time(NULL));

   for (int i = 0; i < 10; i++) {
      accountNumber[i] = '0' + rand() % 10;
  }
  accountNumber[10] = '\0';

  char sql[512];
  snprintf(sql, sizeof(sql),
      "INSERT INTO users(accountNumber, fingerprintId, name, balance) "
        "VALUES('%s', '%s', '%s', '%s');",
        accountNumber, fingerprintId, name, balance);
  
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

double getBalance (const char* accountId) {
  char sql[256];
  sqlite3_stmt *stmt;
  double balance = 0.0;

  sprintf(sql, sizeof(sql),
            "SELECT balance FROM users WHERE accountNumber = '%s';",
            accountId);
  if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
      fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
      return 0.0;
  }

  if (sqlite3_step(stmt) == SQLITE_ROW) {
      balance = sqlite3_column_double(stmt, 0);
  } else {
      printf("Account not found.\n");
  }

  sqlite3_finalize(stmt);
  return balance;
}

void getProfileDetails(const char* accountId) {
  char sql[512];
  sqlite3_stmt *stmt;

  
  snprintf(sql, sizeof(sql),
           "SELECT name, fingerprintId, balance FROM users WHERE accountNumber = '%s';",
           accountId);

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
      fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
      return;
  }

  
  if (sqlite3_step(stmt) == SQLITE_ROW) {
      const char* name = (const char*)sqlite3_column_text(stmt, 0);
      const char* fingerprintId = (const char*)sqlite3_column_text(stmt, 1);
      double balance = sqlite3_column_double(stmt, 2);

      printf("Profile Details:\n");
      printf("Name: %s\n", name);
      printf("Fingerprint ID: %s\n", fingerprintId);
      printf("Balance: %.2f\n", balance);
  } else {
      printf("Account not found.\n");
  }

  sqlite3_finalize(stmt);
  
}

void logout() {
  print("User logged out");
}
