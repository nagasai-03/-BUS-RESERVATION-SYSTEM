#include <iostream>
#include <fstream>
using namespace std;

class bus
{
    string bus_no, bus_driver_name, arrival_time, departure_time, to, from;
    int bus_seats;

public:
    void menu();
    void add_bus_details();
    void display_bus();
    void delete_bus();
    void bus_seats_details();
    void reservation();
    void update_booking();
    void del_booking();
    void show_booking();
};

void decorate(char c)
{
    for(int i=0;i<156;i++)
        cout<<c;
    cout<<endl;
}

void bus::menu()
{
		while(1)
		{
        int choice;
        cout<<endl;
        decorate('-');
        cout << "\n\t\t\t\t\t\t\t\t SRM BUS RESERVATION SYSTEM    \n";
        decorate('-');

        cout << "\n\n\t\t\t\t\t *MAIN MENU*";
        cout << "\n\n\t\t\t\t\t 1. ADD BUS DETAILS";
        cout << "\n\n\t\t\t\t\t 2. DELETE BUS DETAILS"; 
        cout << "\n\n\t\t\t\t\t 3. DISPLAY BUSES"; 
        cout << "\n\n\t\t\t\t\t 4. AVAILABLE SEAT DETAILS "; 
        cout << "\n\n\t\t\t\t\t 5. RESERVATION"; 
        cout << "\n\n\t\t\t\t\t 6. UPDATE BOOKING RECORD"; 
        cout << "\n\n\t\t\t\t\t 7. DELETE BOOKING RECORD"; 
        cout << "\n\n\t\t\t\t\t 8. SHOW ALL BOOKING RECORD"; 
        cout << "\n\n\t\t\t\t\t 9. EXIT";
        cout << "\n\n ENTER YOUR CHOICE: ";
        cin >> choice;
      

        switch (choice)
        {
        case 1:
            add_bus_details();
            break;
        case 2:
            delete_bus();
            break;
        case 3:
            display_bus();
            break;
        case 4:
            bus_seats_details();
            break;
        case 5:
            reservation();
            break;
        case 6:
            update_booking();
            break;
        case 7:
            del_booking();
            break;
        case 8:
            show_booking();
            break;
        case 9:
            {
                cout<<"\n\nProgram successfully exited.";
                exit(0);
        }

        default:
            cout << "Invalid choice";
        }
        
    	}
}

void bus::add_bus_details()
{
here:
	
    fstream file;
    string test_bus_no, test_bus_name, test_driver_name;
    string test_arrival_time, test_departure_time,test_to,test_from; // These variables are for to check whether same variables exist or not
    int test_seats;
    int found = 0; // When no record or file found then found=0

    cout << "\n\n Enter the bus number :";
    cin >> bus_no;

    cout << "\n\n Enter the Driver name : ";
    cin >> bus_driver_name;

    cout << "\n\n Enter the arrival time : ";
    cin >> arrival_time;

    cout << "\n\n Enter the departure time : ";
    cin >> departure_time;

    cout<<"\n\n From :  ";
    cin>>from;

    cout<<"\n\n To : ";
    cin>>to;

    cout << "\n\n Enter the Total Seats : ";
    cin >> bus_seats;


    file.open("bus.txt", ios::in); // To read whether there exisit or not to avoid duplicate of same bus information

    if (!file) // No file exist-->Creating new file
    {
        file.open("bus.txt",  ios::out);

        file << bus_no << " " << bus_driver_name<<" "<< arrival_time << " " << departure_time << " " << from <<" "<<to<<" "<< bus_seats<<" "<< endl;

        file.close();
    }
    else // File exists->Check whether same information is there or not
    {
        file >> test_bus_no>>test_driver_name>>test_arrival_time>>test_departure_time>>test_from>>test_to>>test_seats;
        
        while (!file.eof())
        {
            if (bus_no == test_bus_no)
            {
                found++;
            }
            file >> test_bus_no>>test_driver_name>>test_arrival_time>>test_departure_time>>test_from>>test_to>>test_seats;
            
        }
        file.close();

        if (found == 0) // record no exist(same) -->then copy inside record
        {
            file.open("bus.txt", ios::app | ios::out);

            file << bus_no << " " << bus_driver_name << " "<< arrival_time << " " << departure_time << " " << from <<" "<<to<<" "<< bus_seats<<" "<< endl;

            file.close();
        }

        else
        {
            cout << "\n\n Duplicate Record found";
            goto here;
        }
    }
    cout << "\n\nBus installed successfully.";
}

void bus::delete_bus()
{
    cout<<"\nBuses Avaiable to delete...\n";
    display_bus();

    fstream file,file1;

    string test_bus_num;
    int found = 0;

    file.open("bus.txt",ios::in);

    if(!file)
    {
        cout<<"\n\n Please install the bus details to delete.";
    }
    else
    {
        cout<<"\n\n Enter the bus number to be deleted : ";
        cin>>test_bus_num;

        file1.open("bus1.txt",ios::app|ios::out);
        file>>bus_no>>bus_driver_name>>arrival_time>>departure_time>>from>>to>>bus_seats;

        while(!file.eof())
        {
            if(test_bus_num == bus_no)
            {
                cout<<"\n\n\n Bus has been deleted.";
                found++;
            }
            else{
                file1 << bus_no << " " << bus_driver_name << " "<< arrival_time << " " << departure_time << " " << from <<" "<<to<<" "<< bus_seats<<" "<< endl;
            }

            file>>bus_no>>bus_driver_name>>arrival_time>>departure_time>>from>>to>>bus_seats;
        }

        file.close();
        file1.close();
        remove("bus.txt");
        rename("bus1.txt","bus.txt");
        if(found == 0)
        {
            cout<<"\n\nBus number is Invalid";
        }

    }
}

void bus::display_bus()
{

    fstream file;
    
    file.open("bus.txt", ios::in);

    if (!file) // No file created
    {
        cout << "\n\nPlease install the bus details to view.";
    }

    else
    {
        cout << "\n\n BUS NO.\tDRIVER NAME\tARRIVAL TIME\tDEPARTURE TIME\tFROM\t\tTO\t\tNO. OF SEATS";

        file>>bus_no>>bus_driver_name>>arrival_time>>departure_time>>from>>to>>bus_seats;

        while (!file.eof())
        {
            cout<<"\n"<<bus_no<<"\t\t"<<bus_driver_name<<"\t\t"<<arrival_time<<"\t\t"<<departure_time<<"\t\t"<<from<<"\t\t"<<to<<"\t\t"<<bus_seats<<endl;

            file>>bus_no>>bus_driver_name>>arrival_time>>departure_time>>from>>to>>bus_seats;

        }
    }
    file.close();
   
}

void bus::bus_seats_details()
{
    fstream file,file1; // file --> bus details , file1 -->seats details
    file.open("bus.txt",ios::in);
    file1.open("seat.txt",ios::in);//will come when reservation is used

    string test_bus_no,seats_bus_num,seats_num;
    int count=0; //for reserved seats
    int found=0;

    if(!file || !file1) // File was not found
    {
        cout<<"\n\nPlease install the bus details to view. ";
    }
    else{
        cout<<"\n\n Enter the Bus Number : ";
        cin>>test_bus_no;
        file1>>seats_bus_num>>seats_num;
        while(!file1.eof())
        {
            if(test_bus_no == seats_bus_num)
            {
                count++;
            }
            file1>>seats_bus_num>>seats_num;
        }
        file1.close();

        file>>bus_no>>bus_driver_name>>arrival_time>>departure_time>>from>>to>>bus_seats;
        while(!file.eof())
        {
            if(test_bus_no == bus_no)
            {
                cout<<"\n\n Total number of seats : "<<bus_seats;
                cout<<"\n\n Reserved number of seats : "<<count;
                cout<<"\n\n Empty number of seats : "<<bus_seats-count;

                found++;
                cout<<endl<<endl;
            }
            file>>bus_no>>bus_driver_name>>arrival_time>>departure_time>>from>>to>>bus_seats;
        }
        file.close();

        if(found == 0)
        {
            cout<<"\n\n Bus number is invalid ";
        }
    }
}

void bus:: reservation()
{
    p:

    fstream file;
    file.open("bus.txt",ios::in);
    string test_bus_num,test_bus_num_for_seats,student_name,phone;//test_bus_num_for_seats-->bus num
    int found =0,seat_num,seats,count=0,test_bus_seats; //seat_num selected seat no to book, seats -> total no of seats , count-> To check all seats are reserved or not.
    
	if(!file)
    {
        cout<<"\n\n Please install the bus details to do reservation.";
        
    }
    else
    {
        cout<<"\n\n Enter the bus number: " ;
        cin>>test_bus_num;

        file.close();
        file.open("seat.txt",ios::in);

        if(file) // File exists
        {
            file>>test_bus_num_for_seats>>test_bus_seats;

            while(!file.eof())
            {
                if(test_bus_num == test_bus_num_for_seats)
                    count++;

                file>>test_bus_num_for_seats>>test_bus_seats;
            }

            file.close();
        }

        file.open("bus.txt",ios::in);

        file>>bus_no>>bus_driver_name>>arrival_time>>departure_time>>from>>to>>bus_seats;    
        while(!file.eof())
        {
            if(test_bus_num == bus_no)
            {
                seats = bus_seats;
                found++;
            }

            file>>bus_no>>bus_driver_name>>arrival_time>>departure_time>>from>>to>>bus_seats;
        }

        file.close();

        if(seats - count == 0)
            cout<<"\n\n All seats are reserved";

        else if(found == 1)
        {
            h:

            cout<<"\n\n Enter the Seat number : ";
            cin>>seat_num;
            if(seat_num > seats)
            {
                cout<<"\n\n Seat number is Invalid."<<endl
                    <<"The max number of seats in the bus is "<<seats;
                goto h;
            }
            file.open("seat.txt",ios::in);
            if(!file) //new file ->all seats empty
            {
                file.open("seat.txt",ios::app | ios:: out);

                file<<test_bus_num<<" "<<seat_num<<"\n";

                file.close();
            }
            else // File exist ->To check if the seat is reserveed or not
            {
                file>>test_bus_num_for_seats>>test_bus_seats;
                while(!file.eof())
                {
                    if(test_bus_num == test_bus_num_for_seats && seat_num == test_bus_seats) // bus no and seat no matches
                    {
                        cout<<"\n\n This seat is already reserved";
                        goto h;
                    }

                    file>>test_bus_num_for_seats>>test_bus_seats;
                }
                file.close();

                file.open("seat.txt",ios::app | ios:: out);

                file<<test_bus_num<<" "<<seat_num<<"\n";
                
                file.close();
                
            }

            cout<<"\n\n Enter your name : ";
            cin>>student_name;

            cout<<"\n\n Enter your phone number : ";
            cin>>phone;

            file.open("student.txt",ios::app | ios::in);

            file<<student_name<<" "<<test_bus_num<< " "<<phone<<" "<<seat_num<<endl;

            file.close();

            decorate('*');
            cout<<"\n\n Booking Information \n";
            decorate('*');

            cout<<"\n\n Student Name :          "<<student_name;
            cout<<"\n\n Phone Number :           "<<phone;
            cout<<"\n\n Seat number :            "<<seat_num;
            cout<<"\n\n Booking Succesful";
            cout<<"\n\n Total amount = 60,000";

        }
        else{
            cout<<"\n\n Bus number is Invalid";
            goto p;
        }
    }
}

void bus:: update_booking()
{
    fstream file,file1;
    int reserved_seats,found = 0,t_seats;
    string name,no,phone,t_name,t_phone,del_bus_no;//no-bus no

    file.open("student.txt",ios::in);

    if(!file)
    {
        cout<<"\n\n Please do the reservation to delete.";
    }
    else
    {
        cout<<"\n\n Enter your phone number : ";
        cin>>t_phone;

        file>>name>>no>>phone>>reserved_seats;

        while(!file.eof())
        {
            if(t_phone == phone)
            {
                file.close();
                file.open("student.txt",ios::in);
                file1.open("student1.txt",ios::app|ios::out);
                file>>name>>no>>phone>>reserved_seats;

                while(!file.eof())
                {
                    if(t_phone == phone) // To clear previous seats which were reserved in the previous bookings
                    {
                        del_bus_no = no;
                        t_seats = reserved_seats; //equating the value
                    }

                    if(t_phone != phone)
                    {
                        file1<<name<<" "<<no<<" "<<phone<<" "<<reserved_seats<<endl;
                    }
                    file>>name>>no>>phone>>reserved_seats;
                }
                file.close();
                file1.close();

                remove("student.txt");
                rename("student1.txt","student.txt");

                file.open("seat.txt",ios::in);
                file1.open("seat1.txt",ios::app | ios:: out);

                file>>no>>reserved_seats;
                while(!file.eof())
                {
                    if( !(del_bus_no == no  && reserved_seats == t_seats))
                    {
                        file1<<no<<" "<<reserved_seats<<endl;
                    }
                    file>>no>>reserved_seats;
                }
                file.close();
                file1.close();

                remove("seat.txt");
                rename("seat1.txt","seat.txt");
                
                reservation();
                cout<<"\n\n Updated Reserved Seats";

                found++;
                goto h;
            }
            file>>name>>no>>phone>>reserved_seats;
        }
        file.close();
        h:
        if(found == 0)
        {
            cout<<"\n\n Phone number is Invalid.";
        }
    } 
    
}

void bus:: del_booking()
{
    fstream file,file1;
    int reserved_seats,found = 0,t_seats;
    string name,no,phone,t_name,t_phone,del_bus_no;//no-bus no

    file.open("student.txt",ios::in);

    if(!file)
    {
        cout<<"\n\n Please do the reservation to delete.";
    }
    else
    {
        cout<<"\n\n Enter your phone number : ";
        cin>>t_phone;

        file>>name>>no>>phone>>reserved_seats;

        while(!file.eof())
        {
            if(t_phone == phone)
            {
                file.close();
                file.open("student.txt",ios::in);
                file1.open("student1.txt",ios::app|ios::out);
                file>>name>>no>>phone>>reserved_seats;

                while(!file.eof())
                {
                    if(t_phone == phone) // To clear previous seats which were reserved in the previous bookings
                    {
                        del_bus_no = no;
                        t_seats = reserved_seats; //equating the value
                    }

                    if(t_phone != phone)
                    {
                        file1<<name<<" "<<no<<" "<<phone<<" "<<reserved_seats<<endl;
                    }
                    file>>name>>no>>phone>>reserved_seats;
                }
                file.close();
                file1.close();

                remove("student.txt");
                rename("student1.txt","student.txt");

                file.open("seat.txt",ios::in);
                file1.open("seat1.txt",ios::app | ios:: out);

                file>>no>>reserved_seats;
                while(!file.eof())
                {
                    if( !(del_bus_no == no  && reserved_seats == t_seats))
                    {
                        file1<<no<<" "<<reserved_seats<<endl;
                    }
                    file>>no>>reserved_seats;
                }
                file.close();
                file1.close();

                remove("seat.txt");
                rename("seat1.txt","seat.txt");
                cout<<"\n\n Deleted Reserved Seats.";

                found++;
                goto h;
            }
            file>>name>>no>>phone>>reserved_seats;
        }
        file.close();
        h:
        if(found == 0)
        {
            cout<<"\n\n Phone number is Invalid.";
        }
    }    
}

void bus:: show_booking()
{
    fstream file;
    int reserved_seats,found=0;
    string name,no,phone;

    file.open("student.txt",ios::in);

    if(!file)
    {
        cout<<"\n\n Please do the reservation to view.";
    }
    else
    {
        file>>name>>no>>phone>>reserved_seats;
        while(!file.eof())
        {
        	
            cout<<"\n\n\n Student Name : "<<name;
            cout<<"\n\n Bus Number : "<<no;
            cout<<"\n\n Phone Number : "<<phone;
            cout<<"\n\n Reserved Seat Number : "<<reserved_seats;
            found++;

            file>>name>>no>>phone>>reserved_seats;
        }
        file.close();

        if(found == 0)
            cout<<"\n\n No Booking Record Found.";
    }
}

int main()
{
    bus b;
    b.menu();
}
