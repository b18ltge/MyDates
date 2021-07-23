//23.07.2021
#include <iostream>
#include "MyDates.h"
using namespace std;


namespace MyDates {
    const unsigned short DaysArray[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    void date::SetDay(short NewDay) {
        if (NewDay < 1 || NewDay >((month == 2) ? DaysArray[1] + 1 : DaysArray[1]))
            return;
        day = NewDay;
    }
    short date::GetDay() {
        return day;
    }
    void date::SetMonth(short NewMonth) {
        if (NewMonth < 1 || NewMonth > 12) return;
        month = NewMonth;
    }
    short date::GetMonth() {
        return month;
    }
    void date::SetYear(short NewYear) {
        if (NewYear < 0) return;
        else if (NewYear > 9999) year = 9999;
        year = NewYear;
    }
    short date::GetYear() {
        return year;
    }

    bool IsDateStringCorrect(string MyStringDate) {
        // Check MyStringDate
        if (MyStringDate.length() != 10) return false;
        else if (MyStringDate[2] != '.' || MyStringDate[5] != '.') return false;
        for (size_t i = 0; i < 10; i++)
        {
            if (i == 2 || i == 5)
                continue;
            else if (!isdigit(MyStringDate[i]))
            {
                return false;
            }

        }

        return true;
    }


    bool IsYearLeap(unsigned short year) {
        return (year % 4 || (year % 100 == 0 && year % 400)) ? false : true;
    }

    bool IsDateCorrect(date MyDate) {
        if ((MyDate.GetMonth() > 0 && MyDate.GetMonth() < 13) && (MyDate.GetDay() > 0 && MyDate.GetDay() <= DaysArray[MyDate.GetMonth() - 1]))
            return true;
        else if (IsYearLeap(MyDate.GetYear()) && MyDate.GetMonth() == 2 && MyDate.GetDay() <= 29 && MyDate.GetDay() > 0)
            return true;
        else return false;
    }

    date ConvertStringToDate(string MyStringDate) {
        date tmp;
        if (!IsDateStringCorrect(MyStringDate)) return tmp;

        tmp.SetDay((int(MyStringDate[0]) - 48) * 10 + int(MyStringDate[1]) - 48);
        tmp.SetMonth((int(MyStringDate[3]) - 48) * 10 + int(MyStringDate[4]) - 48);

        for (int i = 6; i < 10; i++)
        {
            tmp.SetYear(tmp.GetYear() * 10);
            tmp.SetYear(tmp.GetYear() + MyStringDate[i] - 48);
        }
        if (!IsDateCorrect(tmp))
        {
            tmp.SetDay(0);
            tmp.SetMonth(0);
            tmp.SetYear(0);
        }

        return tmp;
    }

    /*date::date(const char MyStringDate[11])
    {
        date tmp;
        if (!IsDateStringCorrect(MyStringDate)) return;
        tmp.day = (int(MyStringDate[0]) - 48) * 10 + int(MyStringDate[1]) - 48;
        tmp.month = (int(MyStringDate[3]) - 48) * 10 + int(MyStringDate[4]) - 48;

        tmp.year = 0; // ;)
        for (int i = 6; i < 10; i++)
        {
            tmp.year *= 10;
            tmp.year += MyStringDate[i] - 48;
        }
        if (IsDateCorrect(tmp))
        {
            *this = tmp;
        }
        else
        {
            day = 0;
            month = 0;
            year = 0;
        }
    }*/

    date::date(string MyStringDate)
    {
        date tmp;
        if (!IsDateStringCorrect(MyStringDate)) return;
        if (MyStringDate.length() != 10)
        {
            day = 0;
            month = 0;
            year = 0;
        }
        else {
            tmp.day = (int(MyStringDate[0]) - 48) * 10 + int(MyStringDate[1]) - 48;
            tmp.month = (int(MyStringDate[3]) - 48) * 10 + int(MyStringDate[4]) - 48;

            tmp.year = 0; // ;)
            for (int i = 6; i < 10; i++)
            {
                tmp.year *= 10;
                tmp.year += MyStringDate[i] - 48;
            }
            if (IsDateCorrect(tmp))
            {
                *this = tmp;
            }
            else
            {
                day = 0;
                month = 0;
                year = 0;
            }
        }
    }

    date& date::operator=(string MyStringDate)
    {
        if (!IsDateStringCorrect(MyStringDate)) return *this;
        this->day = (int(MyStringDate[0]) - 48) * 10 + int(MyStringDate[1]) - 48;
        this->month = (int(MyStringDate[3]) - 48) * 10 + int(MyStringDate[4]) - 48;

        this->year = 0; // ;)
        for (int i = 6; i < 10; i++)
        {
            this->year *= 10;
            this->year += MyStringDate[i] - 48;
        }
        if (!IsDateCorrect(*this))
        {
            this->day = 0;
            this->month = 0;
            this->year = 0;
        }
        return *this;
    }

    date& date::operator++ ()
    {
        if (!IsDateCorrect(*this)) return *this;
        if (this->month == 12 && this->day == 31)
        {
            this->year++;
            this->month = 1;
            this->day = 1;
        }
        else if (IsYearLeap(this->year) && this->month == 2 && this->day == 29)
        {
            this->month++;
            this->day = 1;
        }
        else if (IsYearLeap(this->year) && this->month == 2 && this->day == 28)
        {
            this->day++;
        }
        else if (this->day == DaysArray[this->month - 1])
        {
            this->month++;
            this->day = 1;
        }
        else this->day++;

        return *this;
    }

    date& date::operator-- ()
    {
        if (!IsDateCorrect(*this)) return *this;
        if (this->month == 1 && this->day == 1)
        {
            this->year--;
            this->month = 12;
            this->day = 31;
        }
        else if (IsYearLeap(this->year) && this->month == 3 && this->day == 1)
        {
            this->month--;
            this->day = 29;
        }
        else if (this->day == 1)
        {
            this->month--;
            this->day = DaysArray[this->month];
        }
        else this->day--;

        return *this;
    }

    date date::operator++(int)
    {
        if (!IsDateCorrect(*this)) return *this;
        return ++(*this);
    }

    date date::operator--(int)
    {
        if (!IsDateCorrect(*this)) return *this;
        return --(*this);
    }

    date::operator bool() const
    {
        return this->day != 0 || this->month != 0 || this->year != 0;
    }

    date::operator string() const
    {
        string tmp = to_string(this->day / 10) + to_string(this->day % 10) + "." + to_string(this->month / 10) + to_string(this->month % 10) + "." + to_string(this->year / 1000) + to_string((this->year / 100) % 10) + to_string((this->year / 10) % 10) + to_string(this->year % 10);
        return tmp;
    }

    bool operator==(date FirstDate, date SecondDate)
    {
        return ((FirstDate.year == SecondDate.year) && (FirstDate.month == SecondDate.month) && (FirstDate.day == SecondDate.day)) ? true : false;
    }

    bool operator!=(date FirstDate, date SecondDate)
    {
        return !(FirstDate == SecondDate);
    }

    bool operator>(date FirstDate, date SecondDate)
    {
        if (FirstDate.year > SecondDate.year) return true;
        else if (FirstDate.year < SecondDate.year) return false;
        else
        {
            if (FirstDate.month > SecondDate.month) return true;
            else if (FirstDate.month < SecondDate.month) return false;
            else
            {
                if (FirstDate.day > SecondDate.day) return true;
                else if (FirstDate.day < SecondDate.day) return false;
                else return false;
            }
        }
    }

    bool operator>=(date FirstDate, date SecondDate)
    {
        return ((FirstDate > SecondDate) || (FirstDate == SecondDate));
    }

    bool operator<(date FirstDate, date SecondDate)
    {
        return !(FirstDate > SecondDate);
    }

    bool operator<=(date FirstDate, date SecondDate)
    {
        return ((FirstDate < SecondDate) || (FirstDate == SecondDate));
    }

    ostream& operator<<(ostream& out, const date& MyDate)
    {
        out << MyDate.day / 10 << MyDate.day % 10 << "." << MyDate.month / 10 << MyDate.month % 10 << "." << MyDate.year / 1000 << (MyDate.year / 100) % 10 << (MyDate.year / 10) % 10 << MyDate.year % 10;
        return out;
    }

    istream& operator>>(istream& in, date& MyDate) {
        char MyStringDate[11];
        in.getline(MyStringDate, 11);
        if (!IsDateStringCorrect(MyStringDate)) return in;
        MyDate.day = (int(MyStringDate[0]) - 48) * 10 + int(MyStringDate[1]) - 48;
        MyDate.month = (int(MyStringDate[3]) - 48) * 10 + int(MyStringDate[4]) - 48;

        MyDate.year = 0; // ;)
        for (int i = 6; i < 10; i++)
        {
            MyDate.year *= 10;
            MyDate.year += MyStringDate[i] - 48;
        }
        if (!IsDateCorrect(MyDate))
        {
            MyDate.day = 0;
            MyDate.month = 0;
            MyDate.year = 0;
        }
        return in;
    }

    int operator-(date& FirstDate, date& SecondDate)
    {
        if (!IsDateCorrect(FirstDate) || !IsDateCorrect(SecondDate)) return -1;
        date tmp;
        bool MyBool = false;
        if (FirstDate < SecondDate)
        {
            tmp = FirstDate;
            FirstDate = SecondDate;
            SecondDate = tmp;
            MyBool = true;
        }

        int Result = 0;
        int FirstDays = FirstDate.day;
        int SecondDays = SecondDate.day;

        for (short i = SecondDate.year; i < FirstDate.year; i++)
            FirstDays += 365 + IsYearLeap(i);

        for (short i = 0; i < FirstDate.month - 1; i++)
            FirstDays += DaysArray[i];
        if (IsYearLeap(FirstDate.year) && (FirstDate.month > 2))
            FirstDays++;

        for (short i = 0; i < SecondDate.month - 1; i++)
            SecondDays += DaysArray[i];
        if (IsYearLeap(SecondDate.year) && (SecondDate.month > 2))
            SecondDays++;

        if (MyBool)
        {
            tmp = SecondDate;
            SecondDate = FirstDate;
            FirstDate = tmp;
        }

        return FirstDays - SecondDays;

    }

}