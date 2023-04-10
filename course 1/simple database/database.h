#pragma once
#include <iostream>

struct RoomForSale {
    int id_;
    char date_[11];
    int price_;
    int numberOfRooms_;
    int floorNumber_;
    int area_;
    char address_[64];
};

struct DataBase {
    int count_;
    RoomForSale* data_;
};

std::ostream& operator<< (std::ostream& out, const RoomForSale& room);
int add(DataBase&, char*);
int load(DataBase& DB, const char filename[]);
void save(const DataBase& DB, const char filename[]);
int findID(const DataBase& DB, int n);
int find(DataBase& DB, int n);
void deleteID(DataBase&, int);
void exportDB(const DataBase& DB, const char fname[]);
bool compByPrice(const RoomForSale& left, const RoomForSale& right);
void sortByPrice(RoomForSale* M, int n, bool compByPrice(const RoomForSale&, const RoomForSale&));
void printDB(const DataBase&);

int myStrlen(const char word[]);
int myStrcmp(const char* choice, const char word[]);