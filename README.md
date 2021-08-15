![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/Anthony-T-N/Bookmark_Counter)
![C++](https://img.shields.io/badge/Language-C%2B%2B-ff69b4)
![version](https://img.shields.io/badge/version-1.0.0-yellow.svg)
![support](https://img.shields.io/badge/OS-Windows-orange.svg)

# Bookmark_Counter

Overview
-
I somehow managed to accumulate up to 10,495 bookmarks on my default internet browser as of writing this sentence. It would appear I've bookmarked anything I considered remotely interesting and never found the time to go through them. Which is why I've created this console application to assist me with keeping track of the total number of bookmarks I have per day and have data better organised which I hope to use later to create graphs.

How It Works
-
Console application accepts a number (Example: Total number of bookmarks for the current day).
The difference is calculated between the current and previous totals. Converted as a entry with corresponding date.
Stored as a row in csv file.

- Structure of data in csv file:
- Date       | Total  | Difference
- 2021.07.30 | 10,123 | -6
- 2021.07.31 | 10,133 | +10

Usage Overview
-
Upon execution of the application. Simply enter a number.
