#ifndef ACCOUNT_H
#define ACCOUNT_H

void showMenu(const char* accountId);
double getBalance(const char* accountId);
void getProfileDetails(const char* userid);
void logout();
void createUser(const char* name, const char* fingerprintId);
int verifyPin(const char* pin);


#endif


