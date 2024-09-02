#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#define NOMIXMAX
#include <iostream>
#include <functional>
#include <clocale>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <cstdio>
#include <cstring>
#include<limits>
#include <windows.h>
#include <stdexcept>
#define STEP 10
using namespace std;
typedef struct
{
    int number;
    char staton[10];
    int start_time;
    int road_time;
    unsigned int tickets;
    char type; // 0 - пассажирский 1 - грузовой
    union
    {
        int count_pasengers;
        int weight;
    } diff;
} datatype;

struct node
{
    datatype *data;
    struct node * next, * prev;
    node()
    {
        next = nullptr;
        prev = nullptr;
    }
};

class List
{
private:
    node * listleft;
    node * listright;
public:
    friend node * addobj(List &, datatype *);
    int deleteobj (int (*) (datatype *, datatype *), datatype* );
    List (const List &);
    List();
    ~List();
    int newnode(datatype *, node * );
    void includeobject(int (*) (datatype *, datatype *), datatype *);
    node * Getleft();
    node * Getright();
    void Setleft(node * );
    void Setright(node * );
    void deletenode(node *);
    void showlist(int (*) (datatype *, datatype*));
    void print();
    List& operator = (List& );
};

class File
{
    string namefile;
public:
    void Setnamefile(string );
    void readfile(List &);
    int writefile(List& );
};
int cmp_numbers(datatype *, datatype *);
int cmp_stations(datatype *, datatype *);
int cmp_start_time(datatype *, datatype *);
int cmp_road_time(datatype *, datatype *);
int cmp_tickets(datatype *, datatype *);
int notcmp_numbers(datatype * , datatype * );
int notcmp_stations(datatype * , datatype * );
int notcmp_start_time(datatype * , datatype * );
int notcmp_road_time(datatype * , datatype * );
int notcmp_tickets(datatype * , datatype * );
int cmp_fornum(datatype *, datatype *);
int cmp_forstations(datatype *, datatype *);
int cmp_forstart_time(datatype *, datatype *);
int cmp_forroad_time(datatype *, datatype *);
int cmp_fortickets(datatype *, datatype *);
int cmp_forweight(datatype * a, datatype * b);
int cmp_forcount(datatype * a, datatype * b);
int cmp_count(datatype * a, datatype * b);
int cmp_weight(datatype * a, datatype * b);
int notcmp_weight(datatype * a, datatype * b);
int notcmp_count(datatype * a, datatype * b);
datatype *fillobj();
void get_inf(List &, int numer);
void findtrains(List, int, int, const char *);
template <typename T>
void fill_data(string , T &, function<bool(T&)> );
#endif // HEADER_H_INCLUDED
