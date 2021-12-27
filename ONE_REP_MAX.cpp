// Created by Joseph Charboneau on 12/19/21.
// ONE REP MAX CALCULATOR


#include <iostream>
#include <map>
using namespace std;

class Weight_Error
{
};
class Info_Error
{
};
class Exercise_Choice_Error
{
};
bool check_exercise_choice(int choice);
void print_instructions();

class User
{
private:
    string name;
    double lbs_weight;
    double kg_weight;
    string gender;
    // Kg or Lbs
    int weight_choice;
    // Which max the user wants to calculate
    int exercise_choice;
    // Holds lift name in key with max amount in value
    map<string, int> lifts_and_maxes;
    // Each lift's key is a designated number for that lift
    map<int, string> lifts;
    
public:
    // Default Constructor
    User()
    : name(""), kg_weight(0), lbs_weight(0), weight_choice(0), gender(""),
      exercise_choice(0)
    {
    }
    
    // Map assigns a number to each specific lift
    void fill_lifts_map()
    {
        lifts[1] = "Bench";
        lifts[2] = "Squat";
        lifts[3] = "Deadlift";
    }
    
    // Get user's weight
    int get_weight()
    {
        if(weight_choice == 1)
        {
            return kg_weight;
        }
        return lbs_weight;
    }
    
    // Get user's name
    string &get_name()
    {
        return name;
    }
    
    // Converts lbs to kgs
    double lbs_to_kgs(double lbs)
    {
        return lbs * 0.453592;
    }
    
    // Converts kgs to lbs
    double kgs_to_lbs(double kgs)
    {
        return kgs / 0.453592;
    }
    
    // Calculate a max lift given a specific weight, and reps with that weight
    double calculate_max(double weight, double reps)
    {
        if(weight_choice == 1)
        {
            return weight / (1.0278 - (0.0278 * reps));
        }
        return kgs_to_lbs(lbs_to_kgs(weight) / (1.0278 - (0.0278 * reps)));
    }
    
    void print_welcome_message()
    {
        Weight_Error weight_error;
        weight_choice = 0;
        cout << "       Welcome to the ONE REP MAX CALULATOR" << endl;
        cout << "       ------------------------------------" << endl << endl;
        while(weight_choice != 1 && weight_choice != 2)
        {
            cout << "Please choose 1 for kg or 2 for lbs: ";
            try
            {
                cin >> weight_choice;
                if(weight_choice != 1 && weight_choice !=2)
                {
                    throw weight_error;
                }
            }
            catch(Weight_Error)
            {
                cout << endl << "Invalid Choice Entered..." << endl;
                weight_choice = 0;
            }
        }
    }
    
    void print_statistics()
    {
        cout << endl << "*** " << name << "'s Statistics ***" << endl << endl;
        cout << "GENDER: " << gender << endl;
        cout << "WEIGHT: ";
        if(weight_choice == 1)
        {
            cout << kg_weight << " kgs" << endl << endl;
        }
        else
        {
            cout << lbs_weight << " lbs" << endl << endl;
        }
        for(pair<string, double> p : lifts_and_maxes)
        {
            cout << "ONE REP MAX FOR " << p.first << ": " << p.second << endl;
            if(weight_choice == 1)
            {
                if(p.second > kg_weight)
                {
                    cout << "   CONGRATS! You can " << p.first << " more than your body weight!";
                }
            }
            else
            {
                if(p.second > lbs_weight)
                {
                    cout << "   CONGRATS! You can " << p.first << " more than your body weight!";
                }
            }
            cout << endl << endl;
        }
    }
    
    // Gather user's information
    void gather_info()
    {
        Info_Error info_error;
        cout << endl << "Enter First Name: ";
        cin >> name;
        cout << endl << "Enter Weight: ";
        if(weight_choice == 1)
        {
            cin >> kg_weight;
        }
        else
        {
            cin >> lbs_weight;
            kg_weight = lbs_to_kgs(lbs_weight);
        }
        while(gender != "Male" && gender != "Female")
        {
            try
            {
                cout << endl << "Enter Female or Male: ";
                cin >> gender;
                if(gender != "Male" && gender != "Female")
                {
                    throw info_error;
                }
                cout << endl << endl;
            }
            catch(Info_Error)
            {
                cout << "Invalid Gender Entered..." << endl;
            }
        }
    }
    
    // Prompt user to pick which lifts they would like to calculate maxes for
    void lift_choice()
    {
        Exercise_Choice_Error exercise_choice_error;
        while(exercise_choice == 0)
        {
            try
            {
                cin >> exercise_choice;
                if(!check_exercise_choice(exercise_choice))
                {
                    throw exercise_choice_error;
                }
            }
            catch(Exercise_Choice_Error)
            {
                exercise_choice = 0;
                cout << endl << "Invalid Choice..." << endl;
                cout << "Enter \"4\" to calculate all exercises. Otherwise, ";
                cout << "enter the number of the exercise you would like ";
                cout << "to calculate a max for: ";
            }
        }
        cout << endl << endl;
    }
    
    // Prompt user for lift statistics, then calculate a max for given lift
    void calculate_for_lift(string &lift)
    {
        double reps;
        double weight_amount;
        cout << "Enter a known weight and the amount of " << lift << " reps you can do with said weight (reps below 30)" << endl;
        cout << "WEIGHT LIFTED: ";
        cin >> weight_amount;
        cout << "REPS: ";
        cin >> reps;
        cout << endl;
        lifts_and_maxes[lift] = calculate_max(weight_amount, reps);
    }
    
    // Calculate user's chosen maxes
    void calculate_maxes()
    {
        if(exercise_choice == 4)
        {
            for(pair<int,string> p : lifts)
            {
                calculate_for_lift(p.second);
            }
        }
        else
        {
            calculate_for_lift(lifts[exercise_choice]);
        }
    }
};


int main()
{
    User currentUser;
    currentUser.fill_lifts_map();
    currentUser.print_welcome_message();
    currentUser.gather_info();
    print_instructions();
    currentUser.lift_choice();
    currentUser.calculate_maxes();
    currentUser.print_statistics();
}


bool check_exercise_choice(int c)
{
    if(c == 1 || c == 2 || c == 3 || c == 4 || c == 5 || c == 6)
    {
        return true;
    }
    return false;
}

void print_instructions()
{
    cout << "[1]: Bench" << endl << "[2]: Squat" << endl << "[3]: Deadlift" << endl;
    cout << "[4]: Calculate All" << endl;
    cout << endl << "Enter \"4\" to calculate all exercises. Otherwise, ";
    cout << "enter the number of the exercise you would like to calculate a max for: ";
}

