#ifndef MYDATES_H
#define MYDATES_H
//23.07.2021
#include <string>
using namespace std;

namespace MyDates {

    bool IsYearLeap(unsigned short year);

    bool IsDateStringCorrect(string MyStringDate);

    class date {
    private:
        //Members
        short day = 0;
        short month = 0;
        short year = 0;
    public:
        //Methods
        void SetDay(short NewDay);
        short GetDay();

        void SetMonth(short NewMonth);
        short GetMonth();

        void SetYear(short NewYear);
        short GetYear();

        //Constructors
        date() {}
        //date(const char MyStringDate[11]);
        date(std::string MyStringDate);

        //Operators
        date& operator=(string MyStringDate);

        date& operator++ (); // ++date

        date& operator-- (); // --date

        date operator++(int); // date++

        date operator--(int); // date--

        friend bool operator==(date FirstDate, date SecondDate);

        friend bool operator!=(date FirstDate, date SecondDate);

        friend bool operator>(date FirstDate, date SecondDate);

        friend bool operator>=(date FirstDate, date SecondDate);

        friend bool operator<(date FirstDate, date SecondDate);

        friend bool operator<=(date FirstDate, date SecondDate);

        friend int operator-(date& FirstDate, date& SecondDate);

        friend ostream& operator<<(ostream& out, const date& MyDate);

        friend istream& operator>>(istream& in, date& MyDate);

        operator bool() const;

        operator string() const;
    };

    bool IsDateCorrect(date MyDate);

    date ConvertStringToDate(string MyStringDate);
}

#endif
