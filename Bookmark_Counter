// Bookmark_Counter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <filesystem>

#pragma warning(disable:4996);

// TODO: Function to get current date.
std::string get_current_date()
{
    // https://stackoverflow.com/questions/16357999/current-date-and-time-as-string/16358264
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];
    time(&rawtime);
    // Error	C4996	'localtime': This function or variable may be unsafe.Consider using localtime_s instead.To disable deprecation, use _CRT_SECURE_NO_WARNINGS.
    timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    return buffer;
}

// TODO: Function to read from csv file.
void write_to_csv(std::string current_date, int current_bookmark_total)
{
    // Function uses: <iostream>, <fstream>, <filesystem>

    std::ofstream output_file;
    if (std::filesystem::exists("bookmark_record.csv") == false)
    {
        std::cout << "[-] Unable to open bookmark_record.csv;" << "\n";
        return;
    }
    // std::ios::app informs program to append and not overwrite.
    output_file.open("bookmark_record.csv", std::ios::app);
    std::cout << "[+] Opened bookmark_record.csv successfully;" << "\n\n";

    // Comma used as seperator in csv files.
    std::cout << current_date << "," << current_bookmark_total << "\n";
    output_file << current_date << "," << current_bookmark_total << "\n";
    output_file.close();

}


int main()
{
    int current_bookmark_total = 0;
    std::cout << "Enter current total: " << "\n";
    std::cin >> current_bookmark_total;
    write_to_csv(get_current_date(), current_bookmark_total);
}



// Each day, enter total number of bookmarks after each cleaning bookmark session.
// Program will store, process and calculate the difference.
// Stores the total value in a csv file which can be used to make graphs. 

// Data structure in csv file:
// Date       | Total  | Difference
// 2021.07.30 | 10,123 | -6
// 2021.07.31 | 10,133 | +10
