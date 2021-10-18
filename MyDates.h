#pragma once
//18.10.2021
#include <string>

namespace MyDates {
    bool IsYearLeap(uint16_t);
    bool IsDateStringCorrect(const std::string&);

    class date {
        short day = 0;
        short month = 0;
        short year = 0;
    public:
        //Methods
        void SetDay(short);
        short GetDay() const;

        void SetMonth(short);
        short GetMonth() const;

        void SetYear(short);
        short GetYear() const;

        void SetDate(short, short, short);

        //Constructors
        date() {}
        date(short, short, short);
        date(const std::string&);

        //Operators
        date& operator=(const std::string&);

        date& operator++ (); // ++date
        date& operator-- (); // --date
        date operator++(int); // date++
        date operator--(int); // date--

        date& operator+=(int);
        date& operator-=(int);
        date operator+(int) const;
        date operator-(int) const;

        bool operator==(const date&) const;
        bool operator!=(const date&) const;
        bool operator>(const date&) const;
        bool operator>=(const date&) const;
        bool operator<(const date&) const;
        bool operator<=(const date&) const;

        friend int operator-(const date&, const date&);
        friend date operator+(int, const date&);

        friend std::ostream& operator<<(std::ostream&, const date&);

        friend std::istream& operator>>(std::istream&, date&);

        operator bool() const;
        operator std::string() const;
    };

    bool IsDateCorrect(const date&);
    date Today();
}
