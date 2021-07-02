#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
//imported lib

#define MAX_PASSENGER 100
#define MAX_TRAIN 10
#define MAX_SEATS 10
//defined few global things
//max trains is the even the total no of trains
//max passengers is the total no of passengers in all trains
//max seats are the no of seats in a single train

typedef struct
{
    char name[20];
    int PNR;
    int train_number;
} ticket;
//structure for the ticket of each person after booking

typedef struct
{
    int train_no;
    char source[6];
    char destination[10];
    int seats_left;
} train_info;
//this is the structure to store information about the trains

typedef struct
{
    int pNr;
    bool book;
} struct_seat;
//this is used for checking the availability of seats in a train
//initially all the book of this array will be false that is before booking. After booking the book value will change to true
//and initially the pnr will be 0 and afterwards the value is going be changed to pnr of the person

ticket tickets[MAX_PASSENGER];
//this will be storing the information about the passengers after the booking has been confirmed

train_info trains[MAX_TRAIN];
// this will be storing the information about the trains so that it can be transfered to the file afterwards

struct_seat seats[MAX_TRAIN][MAX_SEATS];
//this will store the information, if the seats are booked or not

int pnr;
//this is the used to allot pnr to tickets

int seat_count_func(int i);
void enquiry();
void booking();
void cancellation();
void write_to_file();
void write_to_file_ticket_append(int i);
void write_to_file_ticket_rewrite();
//declaration of the functions used

int main(void)
{
    pnr = 0;
    //initialization of pnr

    for (int i = 0; i < MAX_TRAIN; i++)
    {
        for (int j = 0; j < MAX_SEATS; j++)
        {
            seats[i][j].pNr = 0;
            seats[i][j].book = false;
        }
    }
    //here we have initiallized all the element of seats array with 0 for the pnr and false for the book

    char des[10][10] = {"MUMBAI", "JAIPUR", "SURAT", "PUNE", "AHMEDABAD", "HYDERABAD", "BENGALURU", "CHENNAI", "KOLKATA", "NAGPUR"};
    //made an array for inputting it in the main array

    for (int i = 0; i < MAX_TRAIN; i++)
    {
        trains[i].train_no = i + 1;
        //this will allot the trains a particular train no
        strcpy(trains[i].source, "DELHI");
        //as the source of the station is same
        strcpy(trains[i].destination, des[i]);
        //we have in total 5 destination so we have to copy them in the following
        trains[i].seats_left = seat_count_func(i);
    }
    //storing all the train info into the global array so that later we can tranfer that in the file

    write_to_file();
    //this will store all the information about the train in the file

    FILE *fpointer = fopen("Ticket_info.txt", "w");
    //we are inputting information to ticket_info file
    fprintf(fpointer, "NAME || TRAIN-NUMBER || PNR\n");
    fclose(fpointer);

    int case_no = 0;
    while (true)
    {
        printf("\n");
        printf("Welcome to Indian Railways Booking System!!\n");
        printf("What can we help you with?\n\n");
        printf("Case1: Enquiry\n");
        printf("Case2: Booking\n");
        printf("Case3: Cancellation Facilities\n");
        printf("Case4: Quit\n\n");
        //this will be displayed as it is

        while (true)
        {
            char number_no[4];
            //making a string for input

            printf("Enter the case-number between 1 and 4: ");
            scanf("%s", number_no);
            //asked for input

            if (strlen(number_no) == 1)
            //this will check if what we have typed is of lenght 1
            {
                if (isdigit(number_no[0]) != 0)
                    //this will check if what we have typed is an integer or not
                {
                    case_no = atoi(number_no);
                    //this will change the string into a integer
                    break;
                }
            }
            else
            {
                continue;
            }
        }
        //to ask the user for an input

        switch (case_no)
        {
            case 1:
                enquiry();
                break;
                //this is the case for enquiry

            case 2:
                booking();
                break;
                //this is the case for booking

            case 3:
                cancellation();
                break;
                //this is the case for cancellation

            case 4:
                exit(0);
                break;
                //this will exit the code
        }
        //switch statements

        //this comment can be used for checking whether the tickets are getting booked or not
        /*for (int i = 0; i < MAX_TRAIN; i++)
        {
            printf("%i: %i\n", trains[i].train_no, trains[i].seats_left);
        }

        for (int i = 0; i < MAX_TRAIN; i++)
        {
            for (int j = 0; j < MAX_SEATS; j++)
            {
                printf("%i: %i\n", i, seats[i][j].pNr);
                printf("%i: %i\n", i, seats[i][j].book);
            }
        }
        */
    }
}

int seat_count_func(int i)
{
    int seat_count = 0;
    //initialization

    for (int j = 0; j < MAX_SEATS; j++)
    {
        if (!seats[i][j].book)
        //thi is equal to (seats[i][j].book == false)
        {
            ++seat_count;
        }
        //if the book of the seats array is false then it will count that and return;
    }
    return seat_count;
}
//function to count the no. of seats left in the particular train.

void enquiry()
{
    printf("\n\nTrains are only running from Delhi Station\n\n");
    //Disclaimer

    char source[6];
    printf("Enter the name source you want to enquire about: ");
    scanf("%s", source);
    printf("\n");
    //asked for input of source

    for (int i = 0, n = strlen(source); i < n; i++)
    {
        source[i] = toupper(source[i]);
    }
    //as it will be convinient for us to handle with the same case letters so making all the letters into upper case

    //delhi compared
    if (strcmp(source, "DELHI") == 0)
    {
        printf("\n");
        printf("Railway Station available for destination are:\n1. Mumbai\n2. Jaipur\n3. Surat\n4. Pune\n5. Ahmedabad\n6. Hyderabad\n7. Bengaluru\n8. Chennai\n9. Kolkata\n10. Nagpur\n");
        //printing the destination available
        printf("\n");

        char destination[10];
        printf("Name of destination you want enquire about: ");
        scanf("%s", destination);
        printf("\n");
        //users destination

        for (int i = 0, n = strlen(destination); i < n; i++)
        {
            destination[i] = toupper(destination[i]);
        }
        //as it will be convinient for us to handle with the same case letters so making all the letters into upper case

        int count = 0;
        for (int i = 0; i < MAX_TRAIN; i++)
        {
            if (strcmp(destination, trains[i].destination) == 0)
            {
                printf("Train is available to %s.\n", destination);

                if (trains[i].seats_left != 0)
                {
                    printf("Seats available are: %d.\n\n", trains[i].seats_left);
                }
                //this will print the no of seats avaialble
                else
                {
                    printf("Sorry, seats are not available.\n");
                }

                break;
            }

            else
            {
                ++count;
                continue;
            }
        }

        if (count == MAX_TRAIN)
        {
            printf("No trains to the following destination %s.\n", destination);
        }
        //if destination in the alloted is not typed by the user then this will be displayed
    }

    else
    {
        printf("Trains are only available from DELHI and not from %s.", source);
    }
    //if they do not type delhi
    printf("\n\n");
}

//booking
void booking()
{
    printf("\n\nTrains are only running from Delhi Station\n\n");
    //disclaimer

    char source[6];
    printf("Enter the name of Source you want to book ticket from: ");
    scanf("%s", source);
    //asked for an input from the person enquiring

    for (int i = 0, n = strlen(source); i < n; i++)
    {
        source[i] = toupper(source[i]);
    }
    //converted the letters to higher case so that what ever the person types we can compare

    if (strcmp(source, "DELHI") == 0)
    {
        printf("\n");
        printf("Railway Station available for destination are:\n1. Mumbai\n2. Jaipur\n3. Surat\n4. Pune\n5. Ahmedabad\n6. Hyderabad\n7. Bangaluru\n8. Chennai\n9. Kolkata\n10. Nagpur\n");
        printf("\n");

        char destination[10];
        printf("Enter the name of Destination you want travel to: ");
        scanf("%s", destination);
        printf("\n");
        //destination

        for (int i = 0, n = strlen(destination); i < n; i++)
        {
            destination[i] = toupper(destination[i]);
        }
        //converted to upper case

        int count = 0;
        for (int i = 0; i < MAX_TRAIN; i++)
        {
            if (strcmp(destination, trains[i].destination) == 0)
            //checking the destination
            {
                //checking seats left for the pwrticular train
                if (trains[i].seats_left != 0)
                {
                    //checking for which seat is empty
                    for (int j = 0; j < MAX_SEATS; j++)
                    {
                        if (!seats[i][j].book)
                        {
                            //name of the person
                            char name[20];
                            printf("Name of the person you want to book ticket for: ");
                            scanf("%s", name);

                            printf("\n Seat is available for the particular train.\n");

                            printf("\nDo you want to proceed with the booking?(Y/N)\n");
                            char y_n[2];
                            printf("Type Y(for yes) or N(for no): ");
                            scanf("%s", y_n);
                            //permission for proceeding forward

                            if (toupper(y_n[0]) == 'Y')
                            {
                                strcpy(tickets[pnr].name, name);
                                //for name to store in the global array

                                ++pnr;
                                tickets[pnr - 1].PNR = pnr;
                                //for pnr in global array

                                tickets[pnr - 1].train_number = i + 1;
                                //train no in global array

                                seats[i][j].pNr = tickets[pnr - 1].PNR;
                                seats[i][j].book = true;
                                //for updating the occupancy in the train

                                write_to_file_ticket_append(pnr -1);
                                //to append in the respective file

                                //what will be printed after booking
                                printf("\nYou have paid an amount of Rs. 500 for the ticket\n");
                                printf("Congratulations!! Your ticket is booked.\n");
                                printf("\nYour Ticket details: \n");
                                printf("\tSource: DELHI \tDestination: %s\n", destination);
                                printf("\tYour Name: %s\n", name);
                                printf("\tYour Train Number: %d\n", tickets[pnr - 1].train_number);
                                printf("\tYour PNR number is: %d\n", tickets[pnr - 1].PNR);

                                break;
                            }
                            else if(toupper(y_n[0]) == 'N')
                            {
                                printf("\nBooking failed.\n");
                                break;
                            }
                            else
                            {
                                printf("\nPlease type Y or N next time.\n");
                                printf("Retry booking\n");
                                break;
                            }
                        }
                        else
                        {
                            continue;
                        }
                    }

                    trains[i].seats_left = seat_count_func(i);
                    //this will update the seat left in the particular train
                    write_to_file();
                    //this will update the seats left in the global file of trains
                }

                else
                {
                    printf("No seats are available in the train to this destination.\n");
                }
                //if there are no seats available
            }

            else
            {
                ++count;
                continue;
            }
            //search for destination
        }

        if (count == MAX_TRAIN)
        {
            printf("No trains available to the following destination %s.\n", destination);
        }
    }
    else
    {
        printf("Trains are only available from DELHI and not from %s.\n", source);
    }

    printf("\n\n\n\n");
}

//function for cancellation
void cancellation()
{
    printf("\n\nIf you cancel a ticket you will be charged with Rs. 250 those are cancellation charges\n\n");

    int pnrc;
    printf("\nGive the PNR number of your ticket: ");
    scanf("%d", &pnrc);
    printf("\n");
    //pnr cancellation variable

    int train_no_cancel;
    //p is the train no where the ticket is to be caNCELLED

    if (pnrc > pnr || pnrc < 1)
    {
        printf("Sorry! There is no ticket booked with the provided PNR number\n");
    }
    //this will check for the possibilities of pnr

    else
    {
        //so now we will be searching for train no
        train_no_cancel = tickets[pnrc - 1].train_number;

        if (strcmp(tickets[pnrc - 1].name, "NULL") == 0)
        {
            printf("The ticket with PNR: %d has already been cancelled.\n", pnrc);
        }
        else
        {
            for (int i = 0; i < MAX_SEATS; i++)
            {
                if (seats[train_no_cancel - 1][i].pNr == pnrc)
                //comparing the pnr
                {
                    printf("Do you want to proceed with the cancellation?(Y/N)\n");
                    char y_n[2];
                    printf("Type Y(yes) or N(no): ");
                    scanf("%s", y_n);

                    if (toupper(y_n[0]) == 'Y')
                    {
                        seats[train_no_cancel - 1][i].pNr = 0;
                        seats[train_no_cancel - 1][i].book = false;
                        //updated the seats array so that we can allocate that seat to the next person

                        strcpy(tickets[pnrc - 1].name, "NULL");
                        //here we are the changing the name of the person this seat to NULL so that we can cancel this one in the file

                        write_to_file_ticket_rewrite();
                        //here we are re-writing in the file

                        //this will be printed after we cancel a ticket
                        printf("\nYour ticket with PNR: %d has been successfully cancelled.\n", pnrc);
                        printf("You’ve been refunded Rs. 250 after subtracting 50 percentage of booking charges\n");
                        break;
                    }
                    else if(toupper(y_n[0]) == 'N')
                    {
                        printf("\nBooking failed.\n");
                        break;
                    }
                    else
                    {
                        printf("\nPlease type Y or N.\n");
                        printf("Retry cancellation.\n");
                        break;
                    }
                }
                else
                {
                    continue;
                }
            }
        }

        trains[train_no_cancel - 1].seats_left = seat_count_func(train_no_cancel - 1);
        //updating the seats left in the global array
        write_to_file();
        //updating in the train file

    }


    printf("\n\n\n\n");
}

//Trying to write info to a file
void write_to_file()
{
    //opening the file
    FILE *fpointer = fopen("Train_info.txt", "w");
    fprintf(fpointer, "TRAIN-NUMBER || SOURCE || DESTINATION || SEAT-LEFT\n");
    for (int i = 0; i < MAX_TRAIN; i++)
        //train information is beint updated
    {
        fprintf(fpointer, "%d || %s || %s || %d\n", trains[i].train_no, trains[i].source, trains[i].destination, trains[i].seats_left);
    }
    fclose(fpointer);
    //closing the file
}
//this is used to write about the trains in the file

void write_to_file_ticket_append(int i)
{
    //opening the file
    FILE *fpointer = fopen("Ticket_info.txt", "a");
    fprintf(fpointer, "%s || %d || %d\n", tickets[i].name, tickets[i].train_number, tickets[i].PNR);
    fclose(fpointer);
    //closing the file
}
//this will be updating the file with ticket after every booking

void write_to_file_ticket_rewrite()
{
    FILE *fpointer=fopen("Ticket_info.txt", "w");
    fprintf(fpointer, "NAME || TRAIN-NUMBER || PNR\n");
    // ticket information is being rewritten,updated
    for(int i = 0; i < pnr; i++)
    {
        if (strcmp(tickets[i].name, "NULL") != 0)
        {
            fprintf(fpointer, "%s || %d || %d\n", tickets[i].name, tickets[i].train_number, tickets[i].PNR);
        }
        else
        {
            continue;
        }
    }
    fclose(fpointer);
}
//this will rewrite the whole thing in the file of tickets after someone has cancelled a ticket