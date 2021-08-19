/* Assignment.hpp
 * --------------
 * Authors: Darwin Jacob Groskleg
 * Date:    Monday, March 18, 2019
 *
 * Purpose: 
 */
#ifndef ASSIGNMENT_HPP_INCLUDED
#define ASSIGNMENT_HPP_INCLUDED

#include <vector>

class Assignment {
    const char   _letter;
    const int    _deadline;
    const double _percentage;
public:
    static int FinalDeadline(const std::vector<Assignment> assig_list) {
        int last_so_far = 0;
        for (auto &a : assig_list)
            if (a._deadline > last_so_far)
                last_so_far = a._deadline;
        return last_so_far;
    }

    Assignment(char letter, int deadline, double percentage) :
        _letter(letter),
        _deadline(deadline),
        _percentage(percentage)
    {
        assert(deadline >= 1);
    }

    // Assume the first day is day 1
    // and you can complete an assignment on deadline day.
    inline double yield_rate(int day_on_schedule=1) const {
        if (day_on_schedule > _deadline)
            return 0.0;
        else if (day_on_schedule < 1)
            day_on_schedule = 1;
        return _percentage
                / static_cast<double>(_deadline + 1 - day_on_schedule);
    }

    inline char letter() const { return _letter; }
    inline double percentage() const { return _percentage; }
};


#endif // ASSIGNMENT_HPP_INCLUDED
