// Bookmark_Counter.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

#pragma warning(disable:4996);

std::vector<std::string> temp_report = {};

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

int calculate_difference(int current_bookmark_total_input)
{
    // Function uses: <iostream>, <fstream>, <string>

    std::ifstream input_file;
    input_file.open("bookmark_record.csv");
    std::string input_file_line;
    std::string last_input_line;
    while (std::getline(input_file, input_file_line))
    {
        last_input_line = input_file_line;
        temp_report.push_back(input_file_line);
    }
    input_file.close();
    last_input_line.erase(0, last_input_line.find_first_of(",") + 1);
    last_input_line.erase(last_input_line.find_last_of(","), last_input_line.length());
    return current_bookmark_total_input - stoi(last_input_line);
}

void remove_csv_last_line()
{
    std::cout << "Remove last line" << "\n";
    
    std::ifstream input_file;
    input_file.open("bookmark_record.csv");
    
    std::ofstream output_file;
    output_file.open("temp_record.csv");
    
    std::string input_file_line;
    while (std::getline(input_file, input_file_line))
    {
        std::cout << input_file_line << "\n";
        // TODO Fix here:
        if (input_file.eof() == input_file_line)
        {
            std::cout << "Reach end" << "\n";
        }
        output_file << input_file_line << "\n";
    }
    input_file.close();
    output_file.close();
    //std::rename("temp_record.csv", "bookmark_record.csv");
    // remove("temp_record.csv");
}

// TODO: Function to read from csv file.
void write_to_csv(std::string current_date, int current_bookmark_total_input)
{
    // Function uses: <iostream>, <fstream>, <filesystem>

    int difference = 0;
    // output file stream allows you to write contents to a file.
    std::ofstream output_file;
    if (std::filesystem::exists("bookmark_record.csv") == false)
    {
        std::cout << "[!] Creating new bookmark_record.csv;" << "\n";
        output_file.open("bookmark_record.csv", std::ios::app);
        std::cout << "[+] Opened bookmark_record.csv successfully;" << "\n";
        // Adding in column headings.
        output_file << "Date" << "," << "Current Total" << "," << "Difference" << "\n";
        std::cout << "[+] Adding new entry: ";
        std::cout << current_date << "|" << current_bookmark_total_input << "|" << difference << "\n";
        // Comma used as seperator in csv files.
        output_file << current_date << "," << current_bookmark_total_input << "," << difference << "\n";
        temp_report.push_back(current_date + "," + std::to_string(current_bookmark_total_input) + "," + std::to_string(difference));
        output_file.close();
    }
    else
    {
        // std::ios::app informs program to append and not to overwrite.
        output_file.open("bookmark_record.csv", std::ios::app);
        std::cout << "[+] Opened bookmark_record.csv successfully;" << "\n";
        std::cout << "[+] Adding new entry: ";
        difference = calculate_difference(current_bookmark_total_input);
        std::cout << current_date << "|" << current_bookmark_total_input << "|" << difference << "\n";
        // Comma used as seperator in csv files.
        output_file << current_date << "," << current_bookmark_total_input << "," << difference << "\n";
        temp_report.push_back(current_date + "," + std::to_string(current_bookmark_total_input) + "," + std::to_string(difference));
        output_file.close();
    }
}

std::string user_input_validation()
{
    std::cout << "> Enter current total: ";
    std::string user_input;
    std::getline(std::cin, user_input);
    while (std::cin.fail() || user_input.find_first_not_of("0123456789") != std::string::npos || user_input.empty())
    {
        std::cout << "[-] Incorrect input - Please try again: ";
        std::getline(std::cin, user_input);
    }
    return user_input;
}

int main()
{
    std::cout << "=======================================" << "\n";
    std::cout << "- Bookmark_Counter console application" << "\n";
    std::cout << "- Console Application Version: 1.0" << "\n";
    std::cout << "- Created By: Anthony N." << "\n";
    std::cout << "- Current location of executable: " << std::filesystem::current_path() << "\n";
    std::cout << "=======================================" << "\n\n";
    
    while (true)
    {
        // Note: Fails to valid very large numbers.
        int current_bookmark_total_input = stoi(user_input_validation());
        write_to_csv(get_current_date(), current_bookmark_total_input);
        std::cout << "\n";
        if (temp_report.size() > 20)
        {
            for (int i = 20; i > 0; i--)
            {
                std::cout << temp_report[temp_report.size() - i] << "\n";
            }
        }
        else if (temp_report.size() < 20)
        {
            for (int i = temp_report.size(); i > 0; i--)
            {
                std::cout << temp_report[temp_report.size() - i] << "\n";
            }
        }
        std::cout << "\n";
        std::cout << "> Undo ? (y/n): ";
        std::string user_input;
        std::getline(std::cin, user_input);
        if (user_input == "n")
        {
            break;
        }
        else
        {
            remove_csv_last_line();
        }
    }
    std::cout << "[!] END" << "\n";
    std::cout << "[!] Exiting..." << "\n\n";
    system("pause");
    return 0;
}

// Each day, enter total number of bookmarks after each session of cleaning bookmarks.
// Program will store, process and calculate the difference.
// Stores the total value in a csv file which can be used to make graphs. 

// Data structure in csv file:
// Date       | Total  | Difference
// 2021.07.30 | 10,123 | -6
// 2021.07.31 | 10,133 | +10
