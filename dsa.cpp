#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

struct Event
{
    int id;
    string name;
    int totalSeats;
    float price;
    vector<int> availableSeats;
};

class Events
{
private:
    vector<Event> events;       
    stack<int> bookings;      
    queue<int> waitingQueue;   

public:
    void addEvent()
    {
        Event e;

        cout << "Enter event ID: ";
        cin >> e.id;

        cout << "Enter event name: ";
        cin >> e.name;

        cout << "Enter total seats: ";
        cin >> e.totalSeats;

        cout << "Enter ticket price: ";
        cin >> e.price;

        for (int i = 1; i <= e.totalSeats; i++)
            e.availableSeats.push_back(i);

        events.push_back(e);
        cout << "Event added successfully\n";
    }

    void showEvents()
    {
        for (auto &e : events)
        {
            cout << "ID: " << e.id
                 << " Name: " << e.name
                 << " Seats left: " << e.availableSeats.size()
                 << " Price: " << e.price << endl;
        }
    }

    void bookSeat()
    {
        int eventId;
        cout << "Enter event ID: ";
        cin >> eventId;

        for (auto &e : events)
        {
            if (e.id == eventId)
            {
                if (!e.availableSeats.empty())
                {
                    int seat = e.availableSeats.back(); // choose seat
                    e.availableSeats.pop_back();        // BLOCK
                    bookings.push(seat);                // CONFIRM
                    cout << "Seat " << seat << " booked\n";
                }
                else
                {
                    waitingQueue.push(eventId);
                    cout << "Seats full. Added to waiting list\n";
                }
                return;
            }
        }
        cout << "Event not found\n";
    }

    void cancelTicket()
    {
        if (bookings.empty())
        {
            cout << "No tickets to cancel\n";
            return;
        }

        int seat = bookings.top();
        bookings.pop();
        events[0].availableSeats.push_back(seat);
        cout << "Seat " << seat << " cancelled\n";

        if (!waitingQueue.empty())
        {
            waitingQueue.pop();
            int newSeat = events[0].availableSeats.back();
            events[0].availableSeats.pop_back();
            bookings.push(newSeat);
            cout << "Seat assigned to waiting user\n";
        }
    }
};
int main()
{
    Events em;
    int choice;

    do
    {
        cout << "\n===== TICKET MASTER SYSTEM =====\n";
        cout << "1. Add Event\n";
        cout << "2. Show Events\n";
        cout << "3. Book Seat\n";
        cout << "4. Cancel Ticket\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                em.addEvent();
                break;

            case 2:
                em.showEvents();
                break;

            case 3:
                em.bookSeat();
                break;

            case 4:
                em.cancelTicket();
                break;

            case 0:
                cout << "Thank you for using Ticket Master!\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
