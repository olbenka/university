#include "database.h"
#include <fstream>

std::ostream& operator<< (std::ostream& out, const RoomForSale& room) {
    out << room.id_ << ", " << room.date_ << ", " << room.price_ << ", " <<
        room.numberOfRooms_ << ", " << room.floorNumber_ << ", " << room.area_ << ", " << room.address_ << "." << std::endl;
    return out;
}

int myStrlen(const char word[]) {
    int index = 0;
    int len = 0;
    while (word[index] != '\0') {
        ++len;
        ++index;
    }
    return len;
}

int myStrcmp(const char* choice, const char word[]) {
    int index = 0;
    while (choice[index] != '\0') {
        if (choice[index] != word[index])
            return 1;
        ++index;
    }
    return 0;
}

bool isNum(const char ch) {
    if (ch >= '0' && ch <= '9')
        return 1;
    else if (ch == '.')
        return 1;
    else
        return 0;
}

int checkDate(const char date[]) {
    for (int i = 0; i < myStrlen(date); ++i) {
        if (isNum(date[i]) == 0)
            return 0;
    }

    int day1 = date[0] - '0';
    int day2 = date[1] - '0';
    int month1 = date[3] - '0';
    int month2 = date[4] - '0';

    if (((day1 * 10 + day2) < 1) || ((day1 * 10 + day2) > 31)
        || ((month1 == 0) && (month2 == 2) && ((day1 * 10 + day2) > 28)) ||
        ((month1 == 0) && (month2 == 4) && ((day1 * 10 + day2) > 30)) ||
        ((month1 == 0) && (month2 == 6) && ((day1 * 10 + day2) > 30)) ||
        ((month1 == 0) && (month2 == 9) && ((day1 * 10 + day2) > 30)) ||
        ((month1 == 1) && (month2 == 1) && ((day1 * 10 + day2) > 30))) {
        return 1;
    }
    if (((month1 * 10 + month2) < 1) || ((month1 * 10 + month2) > 12)) {
        return 2;
    }
    return 3;
}

void printDB(const DataBase& DB) {
    for (int i = 0; i < DB.count_; ++i)
        std::cout << DB.data_[i] << std::endl;
}

int strToInt(const char* str) {
    int res = 0;
    for (size_t i = 0; i < myStrlen(str); ++i)
    {
        res = res * 10 + (str[i] - '0');
    }
    return res;
}

bool isUnique(const DataBase& DB, int id) {
    for (int i = 0; i < DB.count_; ++i) {
        if (DB.data_[i].id_ == id) return 0;
        else return 1;
    }
}

int add(DataBase& DB, char* choice) {
    RoomForSale* tmp = new RoomForSale[DB.count_ + 1];
    for (int i = 0; i < DB.count_; ++i)
        tmp[i] = DB.data_[i];
    if (DB.data_)
        delete[] DB.data_;
    DB.data_ = tmp;
    int tmpID = DB.count_ + 1;
    if (isUnique(DB, tmpID))
        DB.data_[DB.count_].id_ = tmpID;
    else {
        bool change = 0;
        while (change == 0) {
            if (isUnique(DB, tmpID) == 0 && tmpID != 0) {
                tmpID -= 1;
                change = 0;
            }
            else {
                DB.data_[DB.count_].id_ = tmpID;
                change = 1;
            }
        }
    }
    char firstWord[128];
    int index = 0;
    int idx = 0;
    while (choice[index] != ' ') {
        firstWord[idx] = choice[index];
        ++index;
        ++idx;
    }
    firstWord[idx] = '\0';
    ++index;
    char newDate[11];
    idx = 0;
    while (choice[index] != ' ') {
        newDate[idx] = choice[index];
        ++idx;
        ++index;
    }
    newDate[idx] = '\0';
    if (checkDate(newDate) == 0) {
        std::cout << "Wrong date format: " << newDate << std::endl;
        return 1;
    }
    else if (checkDate(newDate) == 1) {
        std::cout << "Day value is invalid: " << newDate[0] << newDate[1] << std::endl;
        return 1;
    }
    else if (checkDate(newDate) == 2) {
        std::cout << "Month value is invalid: " << newDate[3] << newDate[4] << std::endl;
        return 1;
    }
    ++index;
    char newNum[128];
    idx = 0;
    while (choice[index] != ' ') {
        newNum[idx] = choice[index];
        ++idx;
        ++index;
    }
    newNum[idx] = '\0';
    ++index;
    char newFloor[128];
    idx = 0;
    while (choice[index] != ' ') {
        newFloor[idx] = choice[index];
        ++idx;
        ++index;
    }
    newFloor[idx] = '\0';
    ++index;
    char newArea[128];
    idx = 0;
    while (choice[index] != ' ') {
        newArea[idx] = choice[index];
        ++idx;
        ++index;
    }
    newArea[idx] = '\0';
    ++index;
    char newAddress[64];
    idx = 0;
    while (choice[index] != ' ') {
        newAddress[idx] = choice[index];
        ++idx;
        ++index;
    }
    newAddress[idx] = '\0';
    ++index;
    char newPrice[128];
    idx = 0;
    while (choice[index] != '\0') {
        newPrice[idx] = choice[index];
        ++idx;
        ++index;
    }
    newPrice[idx] = '\0';
    DB.data_[DB.count_].numberOfRooms_ = strToInt(newNum);
    DB.data_[DB.count_].floorNumber_ = strToInt(newFloor);
    DB.data_[DB.count_].area_ = strToInt(newArea);
    DB.data_[DB.count_].price_ = strToInt(newPrice);
    for (int i = 0; i < 11; ++i) {
        DB.data_[DB.count_].date_[i] = newDate[i];
    }
    for (int i = 0; i < myStrlen(newAddress); ++i) {
        DB.data_[DB.count_].address_[i] = newAddress[i];
    }
    DB.data_[DB.count_].address_[myStrlen(newAddress)] = '\0';
    ++DB.count_;
    return DB.count_;
}

int load(DataBase& DB, const char filename[]) {
    std::ifstream inFile(filename, std::ios_base::binary);
    if (!inFile.is_open()) {
        std::cout << "Can not open file " << filename << std::endl;
        return 0;
    }
    int cnt;
    inFile.read((char*)&cnt, sizeof(int));
    if (DB.data_)
        delete[] DB.data_;
    DB.data_ = new RoomForSale[cnt];
    DB.count_ = cnt;
    inFile.read((char*)DB.data_, sizeof(RoomForSale) * DB.count_);
    inFile.close();
    return cnt;
}

void save(const DataBase& DB, const char filename[]) {
    std::ofstream outFile(filename, std::ios_base::binary); //для работы
    if (!outFile.is_open()) {
        std::cout << "Can not open file " << filename << std::endl;
        return;
    }
    outFile.write((const char*)&DB.count_, sizeof(int));
    outFile.write((const char*)DB.data_, sizeof(RoomForSale) * DB.count_);
    outFile.close();
}

void deleteID(DataBase& DB, int n) {
    int index = findID(DB, n);
    if (index < 0)
        return;
    std::cout << "Are you sure? (Y/N)";
    char ch[128];
    std::cin.getline(ch, 128);
    if (ch[0] == 'Y' || ch[0] == 'y') {
        for (int i = index + 1; i < DB.count_; ++i)
            DB.data_[i - 1] = DB.data_[i];
        --DB.count_;
    }
}

int findID(const DataBase& DB, int n) {
    int tmp = n;
    for (int index = 0; index < DB.count_; ++index) {
        if (DB.data_[index].id_ == tmp)
            return index;
    }
    std::cout << "there are no any rooms with number " << tmp << " in DB" << std::endl;
    return -1;
}

int max(int a, int b) {
    if (a >= b)
        return a;
    else
        return b;
}

int min(int a, int b) {
    if (a <= b)
        return a;
    else
        return b;
}

int find(DataBase& DB, int n) {
    int index = findID(DB, n);
    if (index < 0)
        return -1;
    int rooms = DB.data_[index].numberOfRooms_;
    int floor = DB.data_[index].floorNumber_;
    int space = DB.data_[index].area_;
    for (int i = 0; i < DB.count_; ++i) {
        if ((i != index) && (DB.data_[i].numberOfRooms_ == rooms)
            && (DB.data_[i].floorNumber_ == floor)
            && ((max(DB.data_[i].area_, space) / min(DB.data_[i].area_, space)) <= 1.25))
            return DB.data_[i].id_;
    }
    return -1;
}

void exportDB(const DataBase& DB, const char fname[]) {
    std::ofstream outFile(fname);
    if (!outFile.is_open()) {
        std::cout << "Can not open file " << fname << std::endl;
        return;
    }
    for (int i = 0; i < DB.count_; ++i)
        outFile << DB.data_[i] << std::endl;

    outFile.close();
}

bool compByPrice(const RoomForSale& left, const RoomForSale& right) {
    return left.price_ < right.price_;
}

void sortByPrice(RoomForSale* M, int n, bool compByPrice(const RoomForSale&, const RoomForSale&)) {
    for (int j = 0; j < n - 1; ++j) {
        int minim = j;
        for (int i = minim + 1; i < n; ++i) {
            if (compByPrice(M[i], M[minim]))
                minim = i;
        }
        if (j < minim) {
            std::swap(M[minim], M[j]);
        }
    }
}

