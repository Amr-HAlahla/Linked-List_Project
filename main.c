#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* amr mohammad halahla , 1200902, section 1.*/
//passenger struct.
struct Passenger {
    int id;
    int date;
    char time[20];
    char inDest[20];
    char outDest[20];
    struct Passenger *next;
};
//struct bus
struct Bus {
    int number;
    int date;
    char time[20];
    char inDest[20];
    char outDest[20];
    float price;
    int capacity;
    struct Passenger *head;
    struct Bus *next;
};


void insertPassengers(struct Passenger *, int, int, char[], char[], char[]);

void InsertBusses(struct Bus *listOfBusses, int, int, char[], char[], char[], float, int);

void printPassengers(struct Passenger *);

void printBusses(struct Bus *);

int isEmptyPass(struct Passenger *);

int isEmptyBus(struct Bus *);

int isLastPass(struct Passenger *, struct Passenger *);

int isLastBus(struct Bus *, struct Bus *);

struct Passenger *makeEmpty(struct Passenger *passList);

void DeleteList(struct Passenger *passList);

struct Passenger *FindPassenger(int id, struct Passenger *passList);

struct Passenger *FindPreviousPass(int id, struct Passenger *passList);

void DeletePass(int id, struct Passenger *passList);

void printAssBusses(struct Bus *listOfBus);

struct Bus *FindBus(int number, struct Bus *busList);

struct Bus *FindPreviousBus(int number, struct Bus *busList);

void DeleteBus(int number, struct Bus *busList, struct Passenger *passList);

int main() {

    //define a linked list of passenger to store all passengers.
    struct Passenger *allPass = (struct Passenger *) malloc(sizeof(struct Passenger));
    allPass->next = NULL;
    //define a linked list of bus to store all busses.
    struct Bus *allBus = (struct Bus *) malloc(sizeof(struct Bus));
    allBus->next = NULL;

    char passengerData[50];// to store each passenger's data
    char busData[50];//to store each bus's data

    FILE *file1, *file2;
    file1 = fopen("passengers.txt", "r");
    char tempPassData[5][20];//To store the cut-off data from each line
    if (file1) {// to guarantee that a file exist
        while (fgets(passengerData, sizeof(passengerData), file1)) {//read lines until the end of file.
            int count = 0;
            char *token = strtok(passengerData, "#");
            while (token != NULL) {
                //store cut-off line's data in temp array.
                strcpy(tempPassData[count], token);
                token = strtok(NULL, "#");
                count++;
            }
            //creat new Passenger using the data extracted from the file and added it to the passenger's list.
            insertPassengers(allPass, strtol(tempPassData[0], NULL, 10), strtol(tempPassData[1], NULL, 10),
                             tempPassData[2], tempPassData[3], tempPassData[4]);
        }

    }

    file2 = fopen("busses.txt", "r");
    char tempBusData[7][20];//To store the cut-off data from each bus data lines
    if (file2) { // to guarantee that a file exist
        //read lines from the file until the end.
        while (fgets(busData, sizeof(busData), file2)) {
            int count = 0;
            char *token = strtok(busData, "#");
            while (token != NULL) {
                // store bus data in temp array.
                strcpy(tempBusData[count], token);
                token = strtok(NULL, "#");
                count++;
            }
            // creat new Bus using the data extracted from the file and added it to the list of busses.
            InsertBusses(allBus, strtol(tempBusData[0], NULL, 10), strtol(tempBusData[1], NULL, 10),
                         tempBusData[2], tempBusData[3], tempBusData[4], (float) strtod(tempBusData[5], NULL),
                         strtol(tempBusData[6], NULL, 10));// insert new bus to the linked list
        }
    }
    struct Bus *temp;
    temp = allBus->next;
    //loop to creat a list of passengers for all busses.
    while (temp != NULL) {
        temp->head = NULL;
        // creat the list using a method.
        temp->head = makeEmpty(temp->head);
        temp = temp->next;
    }

    printf("1. Load the bus information file\n"
           "2. Load the passenger information file\n"
           "3. Assign passengers and print assignment information of all Busses\n"
           "4. Print a specific bus information along with its passenger information (names and IDs)\n"
           "5. Print unmatched passengers\n"
           "6. Add new passenger\n"
           "7. Delete passenger\n"
           "8. Delete bus number\n"
           "9. Exit\n");
    int s;//variable to store user selection.
    printf("Enter your selection \n");
    scanf("%d", &s);
    while (s != 9) {
        switch (s) {
            case 1 :
                //print busses information.
                printBusses(allBus);
                printf("---------------------------------\n");
                break;

            case 2:
                //print all passengers' information.
                printPassengers(allPass);
                printf("---------------------------------\n");
                break;

            case 3:
                // assign passengers to suitable bus
                printf("");
                struct Passenger *ptrToPass, *temp2; // pointer of passenger to reach all element in passenger's list.
                struct Bus *ptrToBus;//pointer of bus to reach all element in bus's list.
                ptrToPass = allPass->next;//point to first element in passengers' list.
                while (ptrToPass != NULL) {//loop through whole passengers' list.
                    temp2 = ptrToPass->next;//point ot the first element in bus's list.
                    ptrToBus = allBus->next;
                    int flag = 0;//flag to cut the loop if assign process is done.
                    //loop to remove null char.
                    for (int i = 0; i < 20; ++i) {
                        if (ptrToPass->outDest[i] == '\n')
                            ptrToPass->outDest[i] = '\000';
                    }
                    while (ptrToBus != NULL && !flag) {//loop through whole Buss' list.
                        // loop to remove null char.
                        for (int i = 0; i < 20; ++i) {
                            if (ptrToBus->outDest[i] == '\n')
                                ptrToBus->outDest[i] = '\000';
                        }
                        //check the conditions
                        if (strcmp(ptrToBus->inDest, ptrToPass->inDest) == 0 &&
                            strcmp(ptrToBus->outDest, ptrToPass->outDest) == 0 &&
                            (ptrToBus->date == ptrToPass->date) &&
                            strcmp(ptrToBus->time, ptrToPass->time) == 0 &&
                            ptrToBus->capacity > 0) {
                            //add the passenger to passenger's list inside the suitable bus.
                            insertPassengers(ptrToBus->head, ptrToPass->id, ptrToPass->date, ptrToPass->time,
                                             ptrToPass->inDest,
                                             ptrToPass->outDest);
                            //remove passenger out of the base list after assign process.
                            DeletePass(ptrToPass->id, allPass);
                            ptrToBus->capacity--;//reduce the capacity of the bus.
                            flag = 1;//Indicates that the process was completed correctly
                        }
                        ptrToBus = ptrToBus->next;//reach other busses to check there .
                    }
                    ptrToPass = temp2;//to reach the rest of the passengers' list.
                }
                printAssBusses(allBus);//now print the busses attached with its passengers after assigns' process
                printf("---------------------------------\n");
                break;

            case 4:
                //print specific bus information attached with its passengers.
                printf("Enter Bus number : \n");
                int busNumber;
                scanf("%d", &busNumber);
                struct Bus *result;//pointer of passenger to point to the passenger which has the same number if existed.
                result = FindBus(busNumber, allBus);//search for the passenger by its number.
                if (result != NULL) {//check if the passenger existed. if yes, then print its information.
                    printf("Bus Number : %d \n", result->number);
                    printf("Passengers In This Bus : \n");
                    printPassengers(result->head);
                } else
                    printf("There is no bus have this number\n");

                printf("---------------------------------\n");

                break;

            case 5:
                //print unmatched passengers.
                printf("Unmatched Passengers :\n");
                printPassengers(allPass);
                printf("---------------------------------\n");
                break;

            case 6:
                //add new passenger
                printf("\nEnter complete data for the new Passenger, separated by comma :\n");
                char string[50];//store the data entered by the user.
                char out;
                scanf("%c", &out);//clean buffer.
                scanf("%[^\n]", string);//read data from user.
                //split data using comma.
                int count = 0;
                char *token = strtok(string, ",");//split string by comma.
                char tempArray[5][20];//array of string to store the cut-off data.
                while (token != NULL) {//split string until the end.
                    strcpy(tempArray[count], token);//store each single data in temp array to arrange it.
                    token = strtok(NULL, ",");
                    count++;
                }
                //check if there is already a passenger with this data (same Id).
                struct Passenger *newPtr;
                newPtr = FindPassenger(strtol(tempArray[0], NULL, 10), allPass);
                if (newPtr == NULL) {//if there's no passenger has this id, then you can add the new passenger.
                    //add the passenger to base passengers' list.
                    insertPassengers(allPass, strtol(tempArray[0], NULL, 10), strtol(tempArray[1], NULL, 10),
                                     tempArray[2], tempArray[3], tempArray[4]);
                } else
                    printf("The Passenger With This Id Is Already Exist!\n");

                printf("---------------------------------\n");

                break;

            case 7:
                printf("Enter the number of the passenger you want to delete :\n");
                int passId;
                scanf("%d", &passId);
                struct Passenger *pointer2;
                struct Bus *pointer3;
                pointer3 = allBus->next;
                pointer2 = FindPassenger(passId, allPass);
                if (pointer2 != NULL)
                    DeletePass(passId, allPass);
                else {
                    while (pointer3 != NULL) {
                        pointer2 = FindPassenger(passId, pointer3->head);
                        if (pointer2 != NULL)
                            pointer3->capacity++;
                        DeletePass(passId, pointer3->head);
                        pointer3 = pointer3->next;
                    }
                }
                printf("---------------------------------\n");

                break;

            case 8:
                printf("Enter the Bus number you want to delete :\n");
                int busNumber2;
                scanf("%d", &busNumber2);
                DeleteBus(busNumber2, allBus, allPass);
                printf("---------------------------------\n");

                break;

            default:
                printf("No case with the number %d, please enter number between 1-9 !\n", s);
        }
        printf("1. Load the bus information file\n"
               "2. Load the passenger information file\n"
               "3. Assign passengers and print assignment information of all Busses\n"
               "4. Print a specific bus information along with its passenger information (names and IDs)\n"
               "5. Print unmatched passengers\n"
               "6. Add new passenger\n"
               "7. Delete passenger\n"
               "8. Delete bus number\n"
               "9. Exit\n");
        printf("Enter your selection : \n");
        scanf("%d", &s);
    }
    fclose(file1);
    fclose(file2);
    return 0;
}

int isLastPass(struct Passenger *listOfPass, struct Passenger *pos) {
    return pos->next == NULL;
}

int isLastBus(struct Bus *listOfBus, struct Bus *pos) {
    return pos->next == NULL;
}

void
insertPassengers(struct Passenger *ListOfPass, int id, int date, char time[20], char inDest[20], char outDest[20]) {
    struct Passenger *element = (struct Passenger *) malloc(sizeof(struct Passenger));
    element->id = id;
    element->date = date;
    strcpy(element->time, time);
    strcpy(element->inDest, inDest);
    strcpy(element->outDest, outDest);
    element->next = ListOfPass->next;
    ListOfPass->next = element;
}

void InsertBusses(struct Bus *listOfBusses, int number, int date, char time[20], char inDest[20], char outDest[20],
                  float price, int capacity) {
    struct Bus *element = (struct Bus *) malloc(sizeof(struct Bus));
    element->number = number;
    element->date = date;
    strcpy(element->time, time);
    strcpy(element->inDest, inDest);
    strcpy(element->outDest, outDest);
    element->price = price;
    element->capacity = capacity;
    element->next = listOfBusses->next;
    listOfBusses->next = element;
}

int isEmptyPass(struct Passenger *listOfPass) {
    return listOfPass->next == NULL;
}

int isEmptyBus(struct Bus *listOfBus) {
    return listOfBus->next == NULL;
}

void printPassengers(struct Passenger *listOfPass) {
    struct Passenger *ptr = listOfPass;
    if (isEmptyPass(listOfPass))
        printf("Empty List!\n");
    else {
        ptr = ptr->next;
        while (ptr != NULL) {
            printf("%5d%12d%8s%12s%12s", ptr->id, ptr->date, ptr->time, ptr->inDest, ptr->outDest);
            printf("\n");
            ptr = ptr->next;
        }
        /* do {
             ptr = ptr->next;
             printf("%5d%12d%8s%12s%12s", ptr->id, ptr->date, ptr->time, ptr->inDest, ptr->outDest);
         } while (!isLastPass(listOfPass, ptr));
         printf("\n");*/
    }
}

void printBusses(struct Bus *listOfBus) {
    struct Bus *ptr = listOfBus;
    if (isEmptyBus(listOfBus))
        printf("Empty List!\n");
    else {
        do {
            ptr = ptr->next;
            printf("%-5d%-12d%-8s%-12s%-12s%-4.0f%-4d \n", ptr->number, ptr->date, ptr->time, ptr->inDest,
                   ptr->outDest, ptr->price, ptr->capacity);
        } while (!isLastBus(listOfBus, ptr));
        printf("\n");
    }
}

struct Passenger *makeEmpty(struct Passenger *passList) {
    if (passList != NULL)
        DeleteList(passList);
    passList = (struct Passenger *) malloc(sizeof(struct Passenger));
    if (passList == NULL)
        printf("Out Of Memory!");
    passList->next = NULL;
    return passList;
}

void DeleteList(struct Passenger *passList) {
    struct Passenger *ptr, *temp;
    ptr = passList->next;
    passList->next = NULL;
    while (ptr != NULL) {
        temp = ptr->next;
        free(ptr);
        ptr = temp;
    }
}

struct Passenger *FindPassenger(int id, struct Passenger *passList) {
    struct Passenger *ptr;
    ptr = passList->next;
    while (ptr != NULL && ptr->id != id)
        ptr = ptr->next;
    return ptr;
}

struct Bus *FindBus(int number, struct Bus *busList) {
    struct Bus *ptr;
    ptr = busList->next;
    while (ptr != NULL && ptr->number != number)
        ptr = ptr->next;
    return ptr;
}

struct Passenger *FindPreviousPass(int id, struct Passenger *passList) {
    struct Passenger *ptr;
    ptr = passList;
    while (ptr->next != NULL && ptr->next->id != id)
        ptr = ptr->next;
    return ptr;
}

struct Bus *FindPreviousBus(int number, struct Bus *busList) {
    struct Bus *ptr;
    ptr = busList;
    while (ptr->next != NULL && ptr->next->number != number)
        ptr = ptr->next;
    return ptr;
}

void DeletePass(int id, struct Passenger *passList) {
    struct Passenger *ptr, *temp;
    ptr = FindPreviousPass(id, passList);
    if (!isLastPass(passList, ptr)) {
        temp = ptr->next;
        ptr->next = temp->next; //bypass delete cell
        free(temp);
    }
}

void DeleteBus(int number, struct Bus *busList, struct Passenger *passList) {
    struct Bus *ptr, *temp;
    ptr = FindPreviousBus(number, busList);
    if (!isLastBus(busList, ptr)) {
        temp = ptr->next;
        struct Passenger *ptr2;
        ptr2 = temp->head->next;
        if (ptr2 != NULL) {
            insertPassengers(passList, ptr2->id, ptr2->date, ptr2->time, ptr2->inDest, ptr2->outDest);
        }
        ptr->next = temp->next; //bypass delete cell
        free(temp);
    }
}

void printAssBusses(struct Bus *listOfBus) {
    struct Bus *ptr = listOfBus;
    if (isEmptyBus(listOfBus))
        printf("Empty List!\n");
    else {
        do {
            ptr = ptr->next;
            printf("Bus Information :\n%-5d%-12d%-8s%-12s%-12s%-4.0f%-4d \n", ptr->number, ptr->date, ptr->time,
                   ptr->inDest,
                   ptr->outDest, ptr->price, ptr->capacity);
            printf("\nPassengers In This Bus : \n");
            printPassengers(ptr->head);
            printf("\n");
        } while (!isLastBus(listOfBus, ptr));
        printf("\n\n");
    }
}