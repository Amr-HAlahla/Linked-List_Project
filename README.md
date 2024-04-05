# Bus and Passenger Management System

This program is a simple management system for buses and passengers implemented in C. It allows users to manage passenger and bus data, assign passengers to buses, and perform various operations such as adding, deleting, and printing information.

## Project Overview

The Bus and Passenger Management System consists of two main entities: buses and passengers. Each bus has a unique number, date, time, destination, price, capacity, and a list of passengers. Passengers have an ID, date, time, origin, and destination.

## Features

- Load bus information from a file
- Load passenger information from a file
- Assign passengers to buses based on criteria such as date, time, and destination
- Print information about all buses and their assigned passengers
- Print information about a specific bus and its passengers
- Print unmatched passengers
- Add a new passenger
- Delete a passenger
- Delete a bus

## Getting Started

To compile and run the program, follow these steps:

1. Clone this repository to your local machine.
2. Compile the program using a C compiler. For example:
    ```
    gcc main.c -o bus_management
    ```
3. Run the compiled executable:
    ```
    ./bus_management
    ```


## Usage

Upon running the program, you will be presented with a menu with options to perform various operations. Simply enter the corresponding number for the operation you want to perform and follow the prompts.

## File Formats

The program expects two input files:
1. `busses.txt`: Contains information about buses, with each line formatted as follows:
    `bus_number#date#time#origin#destination#price#capacity`
2. `passengers.txt`: Contains information about passengers, with each line formatted as follows:
    `passenger_id#date#time#origin#destination`

   





