// Bookmark_Counter.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

#pragma warning(disable:4996);

// TODO: Function to get current date.
std::string get_current_date()
{
    // https://stackoverflow.com/questions/16357999/current-date-and-time-as-string/16358264
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];
    time(&rawtime);
    // Error C4996 'localtime': This function or variable may be unsafe.Consider using localtime_s instead.To disable deprecation, use _CRT_SECURE_NO_WARNINGS.
    timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    return buffer;
}

// TODO: Function to read last line of existing csv file.
int calculate_difference(int current_bookmark_total_input)
{
    std::ifstream input_file;
    std::cout << "[!] Opening bookmark_record.csv for reading;" << "\n";
    input_file.open("bookmark_record.csv");
    std::string input_file_line;
    std::string last_input_line;
    while (std::getline(input_file, input_file_line))
    {
        std::cout << input_file_line << "\n";
        last_input_line = input_file_line;
    }
    input_file.close();
    last_input_line.erase(0, last_input_line.find_first_of(",") + 1);
    last_input_line.erase(last_input_line.find_last_of(","), last_input_line.length());
    return current_bookmark_total_input - stoi(last_input_line);
}

// TODO: Function to read from csv file.
void write_to_csv(std::string current_date, int current_bookmark_total_input)
{
    // Function uses: <iostream>, <fstream>, <filesystem>

    // output file stream allows you to write contents to a file.
    std::ofstream output_file;
    if (std::filesystem::exists("bookmark_record.csv") == false)
    {
        std::cout << "[!] Creating new bookmark_record.csv;" << "\n";
        output_file.open("bookmark_record.csv", std::ios::app);
        std::cout << "[+] Opened bookmark_record.csv successfully;" << "\n";
        // Adding in column headings.
        output_file << "Date" << "," << "Current Total" << "," << "Difference" << "\n";
        // Comma used as seperator in csv files.
        output_file << current_date << "," << current_bookmark_total_input << "," << 0 << "\n";
        output_file.close();
    }
    else
    {
        // std::ios::app informs program to append and not to overwrite.
        output_file.open("bookmark_record.csv", std::ios::app);
        std::cout << "[+] Opened bookmark_record.csv successfully;" << "\n";
        // Comma used as seperator in csv files.
        output_file << current_date << "," << current_bookmark_total_input << "," << calculate_difference(current_bookmark_total_input) << "\n";
        output_file.close();
    }
}

int main()
{
    int current_bookmark_total_input = 0;
    std::cout << "Enter current total: " << "\n";
    std::cin >> current_bookmark_total_input;
    write_to_csv(get_current_date(), current_bookmark_total_input);
}

// Each day, enter total number of bookmarks after each session of cleaning bookmarks.
// Program will store, process and calculate the difference.
// Stores the total value in a csv file which can be used to make graphs. 

// Data structure in csv file:
// Date       | Total  | Difference
// 2021.07.30 | 10,123 | -6
// 2021.07.31 | 10,133 | +10
