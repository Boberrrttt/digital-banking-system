#ifndef ACCOUNT_H
#define ACCOUNT_H

double getBalance(const char* accountId);
void getProfileDetails(const char* userId);
void logout();
void createUser(const char* name, const char* fingerprintId, double balance);
int verifyPin(const char* pin);


#endif


