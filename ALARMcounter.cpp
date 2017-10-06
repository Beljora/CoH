#include <string>
#include <fstream>
#include <iostream>
#include <boost/lexical_cast.hpp>


int countALM(int date)
{
    int count = 0;
    bool flag = 0;
    std::string filename(boost::lexical_cast<std::string>(date));
    filename.append("_TEMP.ALM");
    std::ifstream ifs (filename.data(), std::ifstream::in);
    
    if(!ifs) {
             return 0;
    }
    
    std::string word;
    
    while (ifs >> word) {
          if(flag && word.compare("ALARM") == 0)
          count++;
          flag = 0;
          if(word.compare("CFN") == 0)
          flag = 1;
    }
    return count;
}

int main ()
{
    std::ofstream ofs ("Alarm Count.txt", std::ofstream::out);
    int alarms = 0;
    int alarmcount = 0;
    int filecount = 0;
    int average = 0;
    int date = 0;
    int initdate = 170101;
    std::cout << "Enter initial date yearmonth (i.e. 1701): ";
    std::cin >> initdate;
    initdate = initdate * 100 + 1;
    for(int year = 0; year < 21; year++)  {
            for(int month = 0; month < 12; month++) {
                    for(int day = 0; day < 31; day++) {
                            date = initdate+day+month*100+year*10000;
                            alarms = countALM(date);
                            alarmcount += alarms;
                            if (alarms)
                               filecount++;
                    }
                    if(filecount) {
                       average = alarmcount / filecount;
                       ofs << date / 100 % 100 << "/20" << date / 10000 << " Average: " << average << std::endl;
                       average = 0;
                       alarmcount = 0;
                       filecount = 0;
                    }
            }
    }
    return 0;
}
