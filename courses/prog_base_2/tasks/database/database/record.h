#ifndef RECORD_H_INCLUDED
#define RECORD_H_INCLUDED

typedef struct
{
    int id;
    char name [24];
    char surname [24];
    char birthdate[24];
    double budget;
    int years;
} Record;

#endif // RECORD_H_INCLUDED
