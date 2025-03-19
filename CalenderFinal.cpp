/*
JDN = J_OFFSET + 365 + 365*(y-1) + y/4 + 30*m + d - 31) converts Ethiopian calender date to JDN(Julian Day Number)

JDN = 1461 * (y + 4800 + (m - 14) / 12)) / 4 + (367 * (m - 2 - 12 * ((m - 14) / 12))) / 12
    - (3 * ((y + 4900 + (m - 14) / 12) / 100)) / 4 + d - 32075 Converts Gregorian calender date to JDN

r = (JDN - J_OFFSET) % 1461;
n = (r%365) + 365*(r/1460);
year = 4*((JDN-J_OFFSET)/1461) + (r/365) - (r/1460);
month = (n/30) + 1;
day = (n%30) + 1; Converts JDN to Ethiopian calender date

c = jd + 68569;
d = ( 4 * c ) / 146097;
c = c - ( 146097 * d + 3 ) / 4;
a = ( 4000 * ( c + 1 ) ) / 1461001;
c = c - ( 1461 * a ) / 4 + 31;
b = ( 80 * c ) / 2447;
day = c - ( 2447 * b ) / 80;
c = b / 11;
month = b + 2 - ( 12 * c );
year = 100 * ( d - 49 ) + a + c; Converts JDN to Gregorian calender date

weekDay = (JDN+1)%7 + 1; 1 for Sunday, 2 for Monday,...
*/
#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <cstdlib>
using namespace std;
int main()
{
    int greLastDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int ethLastDays[] = {30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 5};
    string daysOfWeek[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    string EthMonths[] = {"MESKEREM", "TIKMIT", "HIDAR", "TAHSAS", "TIR", "YEKATIT", "MEGABIT", "MIAZIA", "GINBOT", "SENE", "HAMLE", "NEHASE", "PAGUME"};

    string GreMonthsForEth[] = {"SEPTEMBER/OCTOBER", "OCTOBER/NOVEMBER", "NOVEMBER/DECEMBER", "DECEMBER/JANUARY", "JANUARY/FEBRUARY", "FEBRUARY/MARCH",
                                "MARCH/APRIL", "APRIL/MAY", "MAY/JUNE", "JUNE/JULY", "JULY/AUGUST", "AUGUST/SEPTEMBER", "SEPTEMBER"};
    //GreMonthsForEth stores the months of Gregorian calender that correspond to each month in the Ethiopian calender
    string GreMonths[] = {"JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE", "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER"};

    string EthMonthsForGre[] = {"TAHSAS/TIR", "TIR/YEKATIT", "YEKATIT/MEGABIT", "MEGABIT/MIAZIA", "MIAZIA/GINBOT", "GINBOT/SENE", "SENE/HAMLE",
                                "HAMLE/NEHASE", "NEHASE/PAGUME/MESKEREM", "MESKEREM/TIKMIT", "TIKMIT/HIDAR", "HIDAR/TAHSAS"};
    //EthMonthsForGre stores the months of Ethiopian calender that correspond to each month in the Gregorian calender

    const int J_OFFSET = 1723856; //value used in conversion of Ethiopian calender date to JDN
    int menuChoice, calChoice; //menuChoice stores a number corresponding to a choice from the menu
                               //calChoice stores a number corresponding to the calender choice. 1 for Ethiopian 2 for Gregorian
    int ethD, ethM, ethY;
    int ethD2, ethM2, ethY2; //store dates in Ethiopian calender
    int greD, greM, greY;
    int greD2, greM2, greY2; //store dates in Gregorian calender
    int daysToAdd; //daysToAdd stores the number of days the user wants to add a date(menu #3)
    int day, month, year; //temporarily store the date from user input
    int JDN, JDN2; //store julian day number values
    char sep1, sep2; //store the characters used to separate day, month and year 1/1/2000 1-1-2000
    bool isValidCal, isValidDay, isValidMonth, isValidYear, isValidSep; //for validation of calender choice and date input respectively
    int hour, hour12, minute, second; //hold the current time "hour" is in 24 hour format and "hour12" is in 12 hour format
    int weekDay, dateDiff, numInputs;
    int a, b, c, d, n, r;
    cout << "----------------WELCOME--------------------" << endl;
    do
    {
        cout << "1. Show local date and time\n2. Convert Date(EC to GC or GC to EC)\n3. Add/Subtract n days to Date(EC  or GC)\n"
            << "4. Date difference between two dates( EC or GC)\n5. Show Zemen(Yohannes, Markos, ...) for EC year\n6. Is Leap year(EC or GC)\n"
            << "7. The weekday for a given date(EC or GC)\n8. Show EC-GC calendar(Primary EC)\n9. Show GC-EC calendar(Primary GC)\n10. Exit\n\n";
        cout << "Menu: ";
        cin >> menuChoice;
        system("cls");
        switch (menuChoice) // for menu 1 calculates and displays local date and time
        {//for the other menus takes calender input from user(1 for Ethiopian calender 2 for Gregorian calender
            case 1:
            {
                time_t ttime = time(0);
                tm *timeNow = localtime(&ttime);
                greY = 1900 + timeNow->tm_year;
                greM = 1 + timeNow->tm_mon;
                greD = timeNow->tm_mday;
                hour = timeNow->tm_hour;
                minute = timeNow->tm_min;
                second = timeNow->tm_sec; //gets current date and time in Gregorian calender

                hour12 = hour % 12;
                if (hour12 == 0)
                    hour12 = 12; //Converts 24-hour format to 12-hour format
                cout << "Local date and time" << endl;
                cout << "Choose calender\n1. EC\n2. GC\n";
                break;
            }
            case 2:
                cout << "Date converter" << endl;
                cout << "1. EC to GC\n2. GC to EC\n";
                break;
            case 3:
                cout << "Add/Subtract days\nChoose calender\n1. EC\n2. GC\n";
                break;
            case 4:
                cout << "Date difference calculator" << endl;
                cout << "Choose Calender.\n1. EC\n2. GC\n";
                break;
            case 5:
                cout << "Show Zemen for a year" << endl;
                calChoice = 1;
                break;
            case 6:
                cout << "Is leap year" << endl;
                cout << "Choose Calender.\n1. EC\n2. GC\n";
                break;
            case 7:
                cout << "Week day" << endl;
                cout << "1. EC\n2. GC\n";
                break;
            case 8:
                calChoice = 1;
                cout << "Ethiopian Calender" << endl;
                break;
            case 9:
                calChoice = 2;
                cout << "Gregorian Calender" << endl;
                break;
            case 10:
                cout << "Exiting...";
                return 0;
            default:
                cout << "INVALID MENU CHOICE!\n\n";
                continue;
        }
        if (menuChoice == 1 || menuChoice == 2 || menuChoice == 3 || menuChoice == 4 || menuChoice == 6 || menuChoice == 7)
        {
            do
            {
                cin >> calChoice;
                isValidCal = calChoice == 1 || calChoice == 2;
                if (!isValidCal)
                    cout << "Input not valid\n";
            }while (!isValidCal);
        }

        numInputs = (menuChoice == 4 ? 2 : (menuChoice == 1 ? 0 : 1));
        for (int i = 1; i <= numInputs; i++) //Two date inputs for menu 4, No date inputs for menu 1 and one date input for the rest
        {
            do
            {
                if (menuChoice == 5 || menuChoice == 6 || menuChoice == 8 || menuChoice == 9) //We only need to accept year for these menu choices
                {
                    day = month = 1;
                    sep1 = sep2 = '/';
                    cout << "Year: ";
                    cin >> year;
                }
                else //We need to accept day, month and year for the other menu choices
                {
                    cout << "\nDate Input (DD/MM/YYYY or DD-MM-YYYY): ";
                    cin >> day >> sep1 >> month >> sep2 >> year;
                }

                if (calChoice == 1) //If the date input from above is in Ethiopian calender
                {
                    if (year % 4 == 3)
                        ethLastDays[12] = 6; //Sets last day of Pagume to 6 days if the year is a leap year
                    else
                        ethLastDays[12] = 5; //otherwise 5

                    isValidDay = (day >= 1 && day <= ethLastDays[month - 1]);
                    isValidMonth = (month >= 1 && month <= 13);
                    isValidYear = (year >= 1575 && year <= 5000);
                    isValidSep = (sep1 == '/' || sep1 == '-') && (sep2 == '/' || sep2 == '-');
                }
                else //If the date input from above is in Gregorian calender
                {
                    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
                        greLastDays[1] = 29; //Sets last day of February to 29  if the year is a leap year
                    else
                        greLastDays[1] = 28; //otherwise 28

                    isValidDay = (day >= 1 && day <= greLastDays[month - 1]); //Evaluates to true if the day input is in range
                    isValidMonth = (month >= 1 && month <= 12); //Evaluates to true if the month input is in range
                    isValidYear = (year >= 1582 && year <= 5000); //Evaluates to true if the year input is in range
                    isValidSep = (sep1 == '/' || sep1 == '-') && (sep2 == '/' || sep2 == '-'); //Evaluates to true if the separators are valid
                }

                if (!isValidDay && isValidMonth) //If the day input is invalid
                    cout << "Error: Day must be 1-" << (calChoice == 1 ? ethLastDays[month - 1] : greLastDays[month - 1]) << endl;
                if (!isValidMonth) //If the month input is invalid
                    cout << "Error: Month must be 1-" << (calChoice == 1 ? "13" : "12") << endl;
                if (!isValidYear) //If the year input is invalid
                    cout << "Error: Year must be " << (calChoice == 1 ? "1575" : "1582") << "-5000" << endl;
                if (!isValidSep) //If the separator input is invalid
                    cout << "Error: Use either / or - as separators." << endl;
            }while (!isValidDay || !isValidMonth || !isValidYear || !isValidSep); //Repeats if there is any invalid input

            if (i == 1 && calChoice == 1) //If date input is for the first time and it is in Ethiopian calender
                ethD = day, ethM = month, ethY = year; //Transfers the date from the temporary variables to the permanent variables
            else if (i == 1 && calChoice == 2) //If date input is for the first time and it is in Gregorian calender
                greD = day, greM = month, greY = year;
            else if (i == 2 && calChoice == 1) //If date input is for the second time and it is in Ethiopian calender
                ethD2 = day, ethM2 = month, ethY2 = year;
            else //If date input is for the second time and it is in Gregorian calender
                greD2 = day, greM2 = month, greY2 = year;

        }
            //The date input shoud be converted to JDN for the following menu choices
            if (calChoice == 1 && (menuChoice == 2 || menuChoice == 3 || menuChoice == 4 || menuChoice == 7))
            { //For Ethiopian calender dates
                JDN = J_OFFSET + 365 + 365*(ethY-1) + ethY/4 + 30*ethM + ethD - 31;
                if (menuChoice == 4) //For menu 4, the second date input should also be converted to JDN
                    JDN2 = J_OFFSET + 365 + 365*(ethY2-1) + ethY2/4 + 30*ethM2 + ethD2 - 31;
            }

            if (calChoice == 2 && (menuChoice == 2 || menuChoice == 3 || menuChoice == 4 || menuChoice == 7))
            { //For Gregorian calender dates
                JDN = (1461 * (greY + 4800 + (greM - 14) / 12)) / 4
                    + (367 * (greM - 2 - 12 * ((greM - 14) / 12))) / 12
                    - (3 * ((greY + 4900 + (greM - 14) / 12) / 100)) / 4
                    + greD - 32075;
                if (menuChoice == 4) //For menu 4, the second date input should also be converted to JDN
                    JDN2 = (1461 * (greY2 + 4800 + (greM2 - 14) / 12)) / 4
                         + (367 * (greM2 - 2 - 12 * ((greM2 - 14) / 12))) / 12
                         - (3 * ((greY2 + 4900 + (greM2 - 14) / 12) / 100)) / 4
                         + greD2 - 32075;
            }

        switch (menuChoice)
        {
            case 1:
                if (calChoice == 2)
                {
                    cout << setfill('0');
                    cout << setw(2) << greD << '/' << setw(2) << greM << '/' << greY << endl;
                    cout << setw(2) << hour12 << ':' << setw(2) << minute << ':' << setw(2) << second
                         << (hour >= 12 ? " PM" : " AM") << endl;
                }
                else
                {
                    JDN = (1461 * (greY + 4800 + (greM - 14) / 12)) / 4
                        + (367 * (greM - 2 - 12 * ((greM - 14) / 12))) / 12
                        - (3 * ((greY + 4900 + (greM - 14) / 12) / 100)) / 4
                        + greD - 32075;
                    r = (JDN - J_OFFSET) % 1461;
                    n = (r%365) + 365*(r/1460);
                    ethY = 4*((JDN-J_OFFSET)/1461) + (r/365) - (r/1460);
                    ethM = (n/30) + 1;
                    ethD = (n%30) + 1;
                    cout << setfill('0')<< setw(2) << ethD << '/' << setw(2) << ethM << '/' << ethY << endl;
                    cout << setw(2) << (hour12 > 6 ? hour12 - 6 : hour12 + 6)  << ':' << setw(2) << minute << ':'
                         << setw(2) << second << (hour >= 6 && hour <= 18 ? " Day" : " Night") << endl;
                }
                cout << setfill(' ');
                break;
            case 2: //If menu choice is 2, until this point, input date was accepted from user, validated and converted to JDN
                if (calChoice == 1) //If calender choice is Ethiopian calender
                {
                    c = JDN + 68569;
                    d = (4 * c) / 146097;
                    c = c - (146097 * d + 3) / 4;
                    a = (4000 * (c + 1)) / 1461001;
                    c = c - (1461 * a) / 4 + 31;
                    b = (80 * c) / 2447;
                    greD = c - (2447 * b) / 80;
                    c = b / 11;
                    greM = b + 2 - (12 * c);
                    greY = 100 * (d - 49) + a + c; //The JDN value is converted to a Gregorian calender date
                    cout << "Equivalent date in Gregorian calender: " << greD << '/' << greM << '/' << greY << endl;
                }
                else //If calender choice is Gregorian calender
                {
                    r = (JDN - J_OFFSET) % 1461;
                    n = (r%365) + 365*(r/1460);
                    ethY = 4*((JDN-J_OFFSET)/1461) + (r/365) - (r/1460);
                    ethM = (n/30) + 1;
                    ethD = (n%30) + 1; //The JDN value is converted to a Ethiopian calender date
                    cout << "Equivalent date in Ethiopian calender: " << ethD << '/' << ethM << '/' << ethY << endl;
                }
                break;
            case 3: //Date input was converted to JDN
                cout << "Days to add(Enter negative value to subtract): ";
                cin >> daysToAdd; //Accepts the number of days to be added the date input
                if(calChoice == 1) //If calender choice is Ethiopian calender
                {
                    JDN += daysToAdd; //we add days to the JDN value and convert it back to a Ethiopian calender date
                    r = (JDN - J_OFFSET) % 1461;
                    n = (r%365) + 365*(r/1460);
                    ethY = 4*((JDN-J_OFFSET)/1461) + (r/365) - (r/1460);
                    ethM = (n/30) + 1;
                    ethD = (n%30) + 1;
                    cout << "New date: " << ethD << '/' << ethM << '/' << ethY << endl;
                }
                else //If calender choice is Gregorian calender
                {
                    JDN += daysToAdd; //we add days to the JDN value and convert it back to a Gregorian calender date
                    c = JDN + 68569;
                    d = (4 * c) / 146097;
                    c = c - (146097 * d + 3) / 4;
                    a = (4000 * (c + 1)) / 1461001;
                    c = c - (1461 * a) / 4 + 31;
                    b = (80 * c) / 2447;
                    greD = c - (2447 * b) / 80;
                    c = b / 11;
                    greM = b + 2 - (12 * c);
                    greY = 100 * ( d - 49 ) + a + c;
                    cout << "New date: " << greD << '/' << greM << '/' << greY << endl;
                }
                break;
            case 4: //Two date inputs were validated and converted to JDN(stored in JDN and JDN2)
                dateDiff = abs(JDN2 - JDN); //To find the difference between the two dates, simply subtract JDN from JDN2
                cout << dateDiff << " Days" << endl; //Absolute value function used to avoid negative results
                break;
            case 5:
                cout << "Zemen: ";
                if (ethY % 4 == 0) //Remainder when year divided by 4 is 0
                    cout << "YOHANNES";
                else if (ethY % 4 == 1) //Remainder is 1
                    cout << "MATIOS";
                else if (ethY % 4 == 2) //Remainder is 2
                    cout << "MARKOS";
                else //Remainder is 3
                    cout << "LUKAS";
                cout << endl;
                break;
            case 6:
                if (calChoice == 1) //Leap year for Ethiopian calender
                {
                    if (ethY % 4 == 3) //Leap year if the remainder is 3 when dividing year by 4
                        cout << "Leap year." << endl;
                    else
                        cout << "Not a leap year" << endl;
                }
                else //Leap year for Gregorian calender
                {
                    if ((greY % 4 == 0 && greY % 100 != 0) || greY % 400 == 0) // Leap year if (year divisible by 4 but not by 100)  OR (divisible by 400)
                        cout << "Leap year." << endl;
                    else
                        cout << "Not a leap year" << endl;
                }
                break;
            case 7: //Date input was accepted, validated and converted to JDN
                weekDay = (JDN+1) % 7 + 1; //1 for Sunday, 2 for Monday, 3 for Tuesday,...
                cout << "Week Day: " << daysOfWeek[weekDay - 1] << endl;
                break;
            case 8:
                int start, // day of the week the week must starts on. Eg. it is 2 if the month starts on Monday and is 1 for the rest of the month
                    stop, // stop is the day of the week the week must ends on.
                    weekStartDay, // The day of the month on the start of the week
                    weekEndDay; // The day of the month on the end of the week
                ethD = ethM = 1; //sets the date to Meskerem 1
                JDN = J_OFFSET + 365 + 365*(ethY-1) + ethY/4 + 30*ethM + ethD - 31; // Converts the date above to JDN
                start = (JDN+1)%7 + 1; //The day of the week Meskerem starts on
                for (; ethM <= 13; ethM++) // 1 iteration = 1 month
                {
                    ethD = 1;
                    cout << "\n__________________________________________\n";
                    cout << " " << EthMonths[ethM - 1] << " " << ethY << "\t" << GreMonthsForEth[ethM - 1] << " ";
                    if (ethM < 4) //Year differnce is 7 before Tahsas
                        cout << ethY + 7;
                    else if (ethM == 4) //In Tahsas, there are two Gregorian years (eth year + 7 and eth year + 8)
                        cout << ethY + 7 << '-' << ethY + 8;
                    else //Year differnce is 8 after Tahsas
                        cout << ethY + 8;
                    cout << "\n _________________________________________" << endl;
                    cout << "|EHU  |SEG  |MAK  |REB  |HAM  |ARB  |QID  |" << endl;
                    cout << "|_____|_____|_____|_____|_____|_____|_____|" << endl;
                    while (ethD <= ethLastDays[ethM - 1]) //1 iteration = 1 week
                    {
                        cout << "|"; //makes the right-most line for the table
                        weekStartDay = ethD; //stores the date the week started at
                        int j;
                        for (j = 1; j < start; j++) // skips the days of the week the month doesn't start at
                            cout  << "     |";
                        for (j = start; j <= 7 && ethD <= ethLastDays[ethM - 1]; j++) //prints the dates for the primary calender(Ethiopian)
                        {
                            cout << right << setw(5) << ethD << "|";
                            ethD++;
                        }
                        weekEndDay = ethD; //stores the date the week end at
                        stop = j; //stores the day of the week printing dates should stop
                        for (int m = stop; m <= 7; m++) //skips the days of the week from where printing stopped until the end of the week
                            cout << "     |";
                        cout << "\n|     |     |     |     |     |     |     |\n";
                        cout << "|"; //makes the right-most line for the table
                        for (j = 1; j < start; j++)
                            cout << "     |";
                        for (int k = weekStartDay; k < weekEndDay; k++) //Converts the dates of the Ethiopian calender to Gregorian calender
                        {
                            JDN = J_OFFSET + 365 + 365*(ethY-1) + ethY/4 + 30*ethM + k - 31;
                            c = JDN + 68569;
                            d = (4 * c) / 146097;
                            c = c - (146097 * d + 3) / 4;
                            a = (4000 * (c + 1)) / 1461001;
                            c = c - (1461 * a) / 4 + 31;
                            b = (80 * c) / 2447;
                            greD = c - (2447 * b) / 80;
                            cout << left << setw(5) << greD << "|";
                        }
                        cout << right; //resets text alignement to right
                        for (int m = stop; m <= 7; m++)
                            cout << "     |";
                        cout << "\n|_____|_____|_____|_____|_____|_____|_____|\n";
                        start = 1;
                    }
                    start = stop;
                    if (start == 8)
                        start = 1;
                }
                break;
            case 9:
                greD = greM = 1;
                JDN = (1461 * (greY + 4800 + (greM - 14) / 12)) / 4 + (367 * (greM - 2 - 12 * ((greM - 14) / 12))) / 12
                    - (3 * ((greY + 4900 + (greM - 14) / 12) / 100)) / 4 + greD - 32075;
                start = (JDN+1)%7 + 1;
                for (greM = 1; greM <= 12; greM++)
                {
                    greD = 1;
                    cout << "\n__________________________________________\n";
                    cout << " " << GreMonths[greM - 1] << " " << greY << "\t" << EthMonthsForGre[greM - 1] << " ";
                    if (greM < 9)
                        cout << greY - 8;
                    else if (greM == 9)
                        cout << greY - 8 << '-' << greY - 7;
                    else
                        cout << greY - 7;
                    cout << endl;
                    cout << " _________________________________________" << endl;
                    cout << "|SUN  |MON  |TUE  |WED  |THU  |FRI  |SAT  |" << endl;
                    cout << "|_____|_____|_____|_____|_____|_____|_____|" << endl;
                    while (greD <= greLastDays[greM - 1])
                    {
                        cout << "|";
                        weekStartDay = greD;
                        int j;
                        for (j = 1; j < start; j++)
                            cout << "     |";
                        for (j = start; j <= 7 && greD <= greLastDays[greM - 1]; j++)
                        {
                            cout << right << setw(5) << greD << "|";
                            greD++;
                        }
                        weekEndDay = greD;
                        stop = j;
                        for (int m = stop; m <= 7; m++)
                            cout << "     |";
                        cout << "\n|     |     |     |     |     |     |     |\n";
                        cout << "|";
                        for (j = 1; j < start; j++)
                            cout << "     |";
                        for (j = weekStartDay; j < weekEndDay; j++)
                        {
                            JDN = (1461 * (greY + 4800 + (greM - 14) / 12)) / 4 + (367 * (greM - 2 - 12 * ((greM - 14) / 12))) / 12
                                - (3 * ((greY + 4900 + (greM - 14) / 12) / 100)) / 4 + j - 32075;
                            r = (JDN - J_OFFSET) % 1461;
                            n = (r%365) + 365*(r/1460);
                            ethD = (n%30) + 1;
                            cout << left << setw(5) << ethD << "|";
                        }
                        for (int m = stop; m <= 7; m++)
                            cout << "     |";
                        cout << "\n|_____|_____|_____|_____|_____|_____|_____|\n";
                        start = 1;
                    }
                    start = stop;
                    if (start == 8)
                        start = 1;
                }
                break;
    }
    system("pause");
    system("cls");
    }while (1);

}
