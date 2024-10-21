#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#pragma warning(disable : 4996)
#include "Header.h";

using namespace Numbers;

using namespace std;

struct strDate
{
    short Month = 12;
    int Days = 31;
    int Year = 2024;
};

int GetDayOrder(int Year, int Month, int Day)
{
    int a = (14 - Month) / 12;
    int y = Year - a;
    int m = Month + (12 * a) - 2;

    return (Day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
}

string DayName(int Year, int Month, int Day)
{
    int DayOrder = GetDayOrder(Year, Month, Day);
    string Days[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

    return Days[DayOrder];
}

int GetNumberOfDaysInMonth(int Year, int Month)
{
    int NumberOfDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    return ((Month == 2) ? LeapYear(Year) ? 29 : 28 : NumberOfDays[Month - 1]);
}

string MonthName(int Month)
{
    string MonthNames[] = { "jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    return MonthNames[Month - 1];
}

void PrintMonthCalendar(int Year, int Month)
{
    int Current = GetDayOrder(Year, Month, 1);
    int i;
    cout << "Sun  Mon  Tue  Wed  Thu  Fri  Sat\n";

    for (i = 0; i < Current; i++)
    {
        cout << "     ";
    }

    for (int j = 1; j <= 30; j++)
    {
        printf(" %0*d  ", 2, j);
        if (++i == 7)
        {
            i = 0;
            cout << endl;
        }
    }
}

int NumberOfDaysTillNow(int Year, int Month, int Days)
{
    int TotalDays = Days;
    for (int i = 1; i < Month; i++)
    {
        TotalDays += GetNumberOfDaysInMonth(Year, i);
    }
    return TotalDays;
}

int GetFutureDate(strDate& Date)
{
    int Days = 1000;


    while ( Days >= 365)
    {
        Date.Year++;

        if (LeapYear(Date.Year))
        {
            Days -= 366;
        }
        else
        {
            Days -= 365;
        }
    }
    return Days;
}

void AddOneDayToDate(strDate& Date)
{
    if (Date.Days == GetNumberOfDaysInMonth(Date.Year, Date.Month))
    {
        if (Date.Month == 12)
        {
            Date.Year++;
            Date.Month = 1;
            Date.Days = 1;
       }
        else
        {
            Date.Month++;
            Date.Days = 1;
        }
    }
    else
    {
        Date.Days++;
    }
}

bool IsDate1BeforeDate2(strDate Date1, strDate Date2)
{
    return (Date1.Year < Date2.Year) ? true : ((Date1.Year ==
        Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month ==
            Date2.Month ? Date1.Days < Date2.Days : false)) : false);
}

bool IsLastDayInMonth(strDate Date)
{
    return (Date.Days == GetNumberOfDaysInMonth(Date.Year,
        Date.Month));
}

bool IsLastMonthInYear(short Month)
{
    return (Month == 12);
}

strDate IncreaseDateByOneDay(strDate Date)
{
    if (IsLastDayInMonth(Date))
    {
        if (IsLastMonthInYear(Date.Month))
        {
            Date.Month = 1;
            Date.Days = 1;
            Date.Year++;
        }
        else
        {
            Date.Days = 1;
            Date.Month++;
        }
    }
    else
    {
        Date.Days++;
    }
    return Date;
}

void SwapDates(strDate &Date1, strDate &Date2)
{
    strDate TempDate = Date1;

    Date1.Year = Date2.Year;
    Date1.Month = Date2.Month;
    Date1.Days = Date2.Days;

    Date2.Year = TempDate.Year;
    Date2.Month = TempDate.Month;
    Date2.Days = TempDate.Days;


}

int GetDiffrence(strDate Date1, strDate Date2, bool IncludeEndDay = false)
{
    int Days = 0;
    short SwapVal = 1;
    if (!IsDate1BeforeDate2(Date1, Date2))
    {
        SwapDates(Date1, Date2);
        SwapVal = -1;
    }
    while (IsDate1BeforeDate2(Date1, Date2))
    {
        Days++;
        Date1 = IncreaseDateByOneDay(Date1);
    }
    return (IncludeEndDay ? ++Days * SwapVal: Days * SwapVal);
}

strDate IncreaseDateByXDays(int Days)
{
    strDate Date;
    int NumOfDaysInMonth;

    while (Days > GetNumberOfDaysInMonth(Date.Year, Date.Month))
    {
        NumOfDaysInMonth = GetNumberOfDaysInMonth(Date.Year, Date.Month);
        if (Days + Date.Month > NumOfDaysInMonth)
        {
            Days -= NumOfDaysInMonth;
            if (IsLastMonthInYear(Date.Month))
            {
                Date.Month = 1;
                Date.Year++;
            }
            else
            {
                Date.Month++;
            }
        }
        else
        {
            Date.Days = Days;
        }
    }

    return Date;
}

strDate IncreaseDateByOneWeek()
{
    strDate Date;
    int Days = 0;
    for (int Day = 1; Day < 7; Day++)
    {
        Days += GetNumberOfDaysInMonth(Date.Year, Date.Month);
    }
    return IncreaseDateByXDays(7);
}

strDate IncreaseDateByXWeeks(int XWeeks)
{
    strDate Date;
    int Days = 0;
    for (int Day = 1; Day < XWeeks * 7; Day++)
    {
        Days += GetNumberOfDaysInMonth(Date.Year, Date.Month);
    }
    return IncreaseDateByXDays(XWeeks * 7);
}

strDate IncreaseDateByOneMonth()
{
    strDate Date;
    
    IsLastMonthInYear(Date.Month) ? Date.Month = 1 : Date.Month++;
    return Date;
}

strDate IncreaseDateByXMonths(int XMonths)
{
    strDate Date;
    return IncreaseDateByXDays(XMonths * 30);
}

strDate IncreaseDateByOneYear()
{
    strDate Date;
    Date.Year++;
    return Date;
}

strDate IncreaseDateByXYears(int XYears)
{
    strDate Date;
    Date.Year += XYears;
    return Date;
}

strDate IncreaseDateByOneDecade()
{
    strDate Date;
    Date.Year += 10;
    return Date;

}

strDate IncreaseDateByXDecades(int XDecades)
{
    strDate Date;
    Date.Year += XDecades * 10;
    return Date;

}

int main()
{
    strDate Date1;

    Date1 = IncreaseDateByXWeeks(12);
    cout << "Add 12 Weeks: ";
    cout << Date1.Year << "/" << Date1.Month << "/" << Date1.Days << endl;

    Date1 = IncreaseDateByOneMonth();
    cout << "Add 1 Month: ";
    cout << Date1.Year << "/" << Date1.Month << "/" << Date1.Days << endl;

    Date1 = IncreaseDateByXMonths(7);
    cout << "Add 7 Month: ";
    cout << Date1.Year << "/" << Date1.Month << "/" << Date1.Days << endl;

    Date1 = IncreaseDateByOneYear();
    cout << "Add 1 Year: ";
    cout << Date1.Year << "/" << Date1.Month << "/" << Date1.Days << endl;

    Date1 = IncreaseDateByXYears(12);
    cout << "Add 12 Year: ";
    cout << Date1.Year << "/" << Date1.Month << "/" << Date1.Days << endl;

    Date1 = IncreaseDateByOneDecade();
    cout << "Add 1 Decade: ";
    cout << Date1.Year << "/" << Date1.Month << "/" << Date1.Days << endl;

    Date1 = IncreaseDateByXDecades(12);
    cout << "Add 12 Decades: ";
    cout << Date1.Year << "/" << Date1.Month << "/" << Date1.Days << endl;


}
