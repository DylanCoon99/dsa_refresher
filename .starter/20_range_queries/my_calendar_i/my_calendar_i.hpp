#pragma once

// A calendar of half-open bookings [start, end).
class MyCalendar {
public:
    // Book [start, end) iff it overlaps no existing booking. Return whether it was booked.
    // A failed call must not change the calendar.
    bool book(int start, int end) {
        // TODO: implement
        return false;
    }

private:
    // Add your fields here.
};
