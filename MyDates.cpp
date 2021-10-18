//18.10.2021
#include <iostream>
#include <sstream>
#include "MyDates.h"

namespace MyDates {
    const static unsigned short DaysArray[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    const static std::string MonthArray[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

    void date::SetDay(short NewDay) {
        if (NewDay < 1 || NewDay >((IsYearLeap(year) && month == 2) ? 29 : DaysArray[month - 1]))
            return;
        day = NewDay;
    }
    short date::GetDay() const {
        return day;
    }
    void date::SetMonth(short NewMonth) {
        if (NewMonth < 1 || NewMonth > 12) return;
        month = NewMonth;
    }
    short date::GetMonth() const {
        return month;
    }
    void date::SetYear(short NewYear) {
        if (NewYear < 0) return;
        else if (NewYear > 9999) NewYear %= 9999;
        year = NewYear;
    }
    short date::GetYear() const {
        return year;
    }
    void date::SetDate(short NewDay, short NewMonth, short NewYear) {
        *this = date(NewDay, NewMonth, NewYear);
    }
    date Today() {
        std::string str = __DATE__;
        std::string MonthStr = str.substr(0, 3);

        short month(0);
        for (uint8_t i(0); i < 12; ++i) {
            if (MonthStr == MonthArray[i])
            {
                month = i + 1;
                break;
            }
        }

        short year = stoi(str.substr(str.length() - 5, 5));
        short day = stoi(str.substr(str.length() - 8, 3));

        return date(day, month, year);
    }

    bool IsDateStringCorrect(const std::string& MyStringDate) {
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
    bool IsYearLeap(uint16_t year) {
        return (year % 4 || (year % 100 == 0 && year % 400)) ? false : true;
    }
    bool IsDateCorrect(const date& MyDate) {
        if ((MyDate.GetMonth() > 0 && MyDate.GetMonth() < 13) && (MyDate.GetDay() > 0 && MyDate.GetDay() <= DaysArray[MyDate.GetMonth() - 1]))
            return true;
        else if (IsYearLeap(MyDate.GetYear()) && MyDate.GetMonth() == 2 && MyDate.GetDay() <= 29 && MyDate.GetDay() > 0)
            return true;
        else return false;
    }

    date::date(short NewDay, short NewMonth, short NewYear) {
        if (NewYear < 0) return;
        else if (NewYear > 9999) NewYear %= 9999;
        else if (NewMonth < 1 || NewMonth > 12)
            return;
        else if (NewDay < 1 || NewDay > ((IsYearLeap(NewYear) && NewMonth == 2) ? 29 : DaysArray[NewMonth - 1]))
            return;

        this->day = NewDay;
        this->month = NewMonth;
        this->year = NewYear;
    }
    date::date(const std::string& MyStringDate)
    {
        if (!IsDateStringCorrect(MyStringDate)) return;
        if (MyStringDate.length() != 10)
        {
            day = 0;
            month = 0;
            year = 0;
        }
        else {
            day = (int(MyStringDate[0]) - 48) * 10 + int(MyStringDate[1]) - 48;
            month = (int(MyStringDate[3]) - 48) * 10 + int(MyStringDate[4]) - 48;
            year = 0; // ;)

            for (int i = 6; i < 10; i++)
            {
                year *= 10;
                year += MyStringDate[i] - 48;
            }
            if (!IsDateCorrect(*this))
            {
                day = 0;
                month = 0;
                year = 0;
            }
        }
    }

    date& date::operator=(const std::string& MyStringDate)
    {
        *this = date(MyStringDate);
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

    date& date::operator+=(int days) {
        *this = *this + days;
        return *this;
    }
    date& date::operator-=(int days) {
        *this = *this - days;
        return *this;
    }

    date date::operator+(int days) const {
        if (days < 0) {
            days *= -1;
            return *this - days;
        }
        date result = *this;
        if (days >= 146097)
        {
            result.year += days / 146097 * 400;
            days %= 146097;
        }

        while (days > 364) {
            if (IsYearLeap(result.year + 1) && days > 365 && result.month > 2)
            {
                ++result.year;
                days -= 366;
            }
            else if (result.month == 2 && result.day == 29) {
                days -= 365;
                result.day--;
                ++result.year;
            }
            else {
                ++result.year;
                days -= 365;
            }
        }

        uint8_t dop;
        while (days) {
            dop = ((result.month == 2 && IsYearLeap(result.year)) ? 29 : DaysArray[result.month - 1]) - result.day + 1;
            if (days >= dop)
            {
                days -= dop;
                if (result.month == 12) {
                    result.month = 1;
                    result.year++;
                }
                else ++(result.month);
                result.day = 1;
            }
            else {
                result.day += days;
                days = 0;
            }
        }

        if (result.year > 9999) result.year %= 9999;
        return result;
    }
    date date::operator-(int days) const {
        if (days < 0)
        {
            days *= -1;
            return *this + days;
        }
        date result = *this;

        if (days >= 146097)
        {
            result.year -= days / 146097 * 400;
            days %= 146097;
        }

        while (days > 364) {
            if (IsYearLeap(result.year) && days > 365 && result.month > 2)
            {
                --result.year;
                days -= 366;
            }
            else if (result.month == 2 && result.day == 29) {
                days -= 365;
                result.day = 1;
                result.month = 3;
                --result.year;
            }
            else {
                --result.year;
                days -= 365;
            }
        }

        short dop;
        while (days) {
            dop = result.day;
            if (days >= dop)
            {
                days -= dop;
                if (result.month == 1) {
                    result.month = 12;
                    result.year--;
                }
                else --(result.month);
                result.day = (IsYearLeap(result.year) && result.month == 2) ? 29 : DaysArray[result.month - 1];
            }
            else {
                result.day -= days;
                days = 0;
            }
        }

        if (result.year < 0) result.year += 10000;
        return result;
    }

    date::operator bool() const
    {
        return this->day != 0 || this->month != 0 || this->year != 0;
    }
    date::operator std::string() const
    {
        std::ostringstream oss;
        oss << *this;
        return oss.str();
    }

    bool date::operator==(const date& OtherDate) const
    {
        return this->year == OtherDate.year && this->month == OtherDate.month && this->day == OtherDate.day;
    }
    bool date::operator!=(const date& OtherDate) const
    {
        return !(*this == OtherDate);
    }
    bool date::operator>(const date& OtherDate) const
    {
        if (this->year > OtherDate.year) return true;
        else if (this->year < OtherDate.year) return false;
        else
        {
            if (this->month > OtherDate.month) return true;
            else if (this->month < OtherDate.month) return false;
            else
            {
                if (this->day > OtherDate.day) return true;
                else if (this->day < OtherDate.day) return false;
                else return false;
            }
        }
    }
    bool date::operator>=(const date& OtherDate) const
    {
        return ((*this > OtherDate) || (*this == OtherDate));
    }
    bool date::operator<(const date& OtherDate) const
    {
        return !(*this >= OtherDate);
    }
    bool date::operator<=(const date& OtherDate) const
    {
        return !(*this > OtherDate);
    }


    int operator-(const date& FirstDate, const date& SecondDate)
    {
        if (!(IsDateCorrect(FirstDate) && IsDateCorrect(SecondDate))) return -1;

        int Days(0);
        int FirstDays = FirstDate.day;
        int SecondDays = SecondDate.day;

        for (short i = std::min(FirstDate, SecondDate).year; i < std::max(FirstDate, SecondDate).year; ++i)
            Days += 365 + IsYearLeap(i);

        for (short i = 0; i < FirstDate.month - 1; ++i)
            FirstDays += DaysArray[i];
        if (IsYearLeap(FirstDate.year) && (FirstDate.month > 2))
            FirstDays++;

        for (short i = 0; i < SecondDate.month - 1; ++i)
            SecondDays += DaysArray[i];
        if (IsYearLeap(SecondDate.year) && (SecondDate.month > 2))
            SecondDays++;

        (FirstDate < SecondDate) ? SecondDays += Days : FirstDays += Days;

        return (FirstDays < SecondDays) ? SecondDays - FirstDays : FirstDays - SecondDays;

    }
    date operator+(int days, const date& MyDate) {
        return MyDate + days;
    }

    std::ostream& operator<<(std::ostream& out, const date& MyDate)
    {
        out << MyDate.day / 10 << MyDate.day % 10 << "." << MyDate.month / 10 << MyDate.month % 10 << "." << MyDate.year / 1000 << (MyDate.year / 100) % 10 << (MyDate.year / 10) % 10 << MyDate.year % 10;
        return out;
    }
    std::istream& operator>>(std::istream& in, date& MyDate) {
        std::string str;
        in >> str;
        MyDate = date(str);
        return in;
    }

}