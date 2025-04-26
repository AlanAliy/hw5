#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here
bool schedule_helper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    size_t day,
    DailySchedule& sched,
    vector<uint> employee_shifts
);

void recursive_adder(
    int number_to_add, 
    vector<uint>& employee_shifts, 
    size_t count, vector<Worker_T>& team
);

void find_all_teams(
    const vector<Worker_T>& available_employees,
    const size_t dailyNeed,
    size_t start,
    vector<Worker_T>& current_team,
    vector<vector<Worker_T>>& all_teams
);

vector<uint> find_available_employees(   
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    size_t day,
    DailySchedule& sched,
    vector<uint> employee_shifts,
    size_t num_employees
);


bool is_valid(
    vector<uint> employee_shifts, 
    uint employee, 
    size_t max_shifts
);




bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    size_t num_employees = avail[0].size();
    vector<uint> employee_shifts(num_employees, 0);
    return schedule_helper(avail, dailyNeed, maxShifts, 0, sched, employee_shifts);


}

bool is_valid(vector<uint> employee_shifts,  uint employee, size_t max_shifts) {
    return employee_shifts[employee] < max_shifts;
}

//finds all available employees given a specific day and the availability matrix.
vector<uint> find_available_employees(   
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    size_t day,
    DailySchedule& sched,
    vector<uint> employee_shifts,
    size_t num_employees
    ) 
    {
        vector<uint> available_employees;
        Worker_T cur_employee = 0;
        
        while(cur_employee < num_employees) {
            if( avail[day][cur_employee] == 1 && 
                is_valid(employee_shifts, cur_employee, maxShifts)) {
                   available_employees.push_back(cur_employee);
                }
            cur_employee++;
        }
        return available_employees;

    }


    //function that will give all combos of teammates into inputted vector
void find_all_teams(
        const vector<Worker_T>& available_employees,
        const size_t dailyNeed,
        size_t start,
        vector<Worker_T>& current_team,
        vector<vector<Worker_T>>& all_teams
    )
    {
        if (current_team.size() == dailyNeed) {
            all_teams.push_back(current_team);
        }

        for (size_t i = start; i < available_employees.size(); i++){ 
            current_team.push_back(available_employees[i]);
            find_all_teams(available_employees, dailyNeed, i+1,current_team, all_teams);
            current_team.pop_back();
        }
    }




//this is a recursive function to add or subtract a number of shifts from the emplyee shifts array
//I would have done this iteratuvely but I can only use 3 loops in this project as a side challenge so hence
//here it is
//its essentialy a for int i = 0, i<team.size(), i++     employee_shifts[team[i]] = + or - 1  loop
void recursive_adder(int number_to_add, vector<uint>& employee_shifts, size_t count, vector<Worker_T>& team)
{
    if (count == team.size()) {
        return;
    }
    employee_shifts[team[count]] += number_to_add;
    recursive_adder(number_to_add, employee_shifts, count+1, team);
}


bool schedule_helper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    size_t day,
    DailySchedule& sched,
    vector<uint> employee_shifts
)
{

        
    if (day == avail.size()) {
        return true;
    }

    size_t num_employees = avail[0].size();
    
    vector<uint> available_employees = find_available_employees(avail, dailyNeed, maxShifts, day, sched, employee_shifts, num_employees);
    vector<Worker_T> current_team;
    vector<vector<Worker_T>> all_teams;
    vector<Worker_T> invalid_IDs(dailyNeed, INVALID_ID);
    
    find_all_teams(available_employees, dailyNeed, 0, current_team, all_teams);

    
    for (uint i = 0; i < all_teams.size(); i++) {
        sched.push_back(all_teams[i]);
        recursive_adder(1, employee_shifts, 0, all_teams[i]);
       
        if(schedule_helper(avail, dailyNeed, maxShifts, day+1, sched, employee_shifts)) {
            return true;
        }
        recursive_adder(-1, employee_shifts, 0, all_teams[i]);
        sched[day] = invalid_IDs;
        sched.pop_back();
    }
    return false;


}
