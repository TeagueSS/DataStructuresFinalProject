#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <set>
#include <stdlib.h>
// CurrentCodingPrompts
using namespace std;
// Creating a struct to hold our player type
struct Player {
    std::string first_name;
    std::string last_name;
    std::string team;
};

// Using our HashTable Class from a previous Assignment:
class HashTable {
private:
    /*
     * Creatig a hashTable that can hold names of up to a length of 28
     * 20 X 28 = 560 possible entries
     Creating our Hash Table which is an array of List pairs
     We are using an array as our data should at maximum have 260 possible key values
     and we are using a pair so that we can have our key attached to our value if we need it
    */
    list<pair<int, Player>> hashTable[560];
    // Creaitng our tombstone constants
    const int tombStoneKey = -1;
    const Player tombStonePlayer = {"-1", "-1", "-1"};


public:
    // Here we are defining the function that allow us to interact with our hash table
    // bool isEmpty() const;
    int buildKey(string name) {

        /*
         * A user's name(String) is an array of characters
         * we can loop through their name using the ASCII table conversion to build
         * their key value
         *
         */
        // Creating a return key which we are summing for
        int returnKey = 0;
        // Looping for each value in our name
        for (int counter = 0; counter < name.length(); counter++) {
            // and adding it's value if it is greater than 65
            if (name[counter] > 65) {
                // Adding our value - 65 to make our key
                returnKey += (name[counter] - 65);
            }
        }
        return returnKey;
    };

    int insertPlayer(string name, Player ourPlayer) {
        // Building the key out of our value
        int key = buildKey(name);

        // Adding our value to the back of the list at our hash table
        hashTable[key].emplace_back(key, ourPlayer);
        // Printing out our location
        cout << "Adding Value: " << name << " With Key: " << key << " The Current List Length At that Location is: " <<
             hashTable[key].size() << endl;
        return hashTable[key].size();
    };

};

/* FindRepeatPlayers
 *
 * Purpose:
 * Here we take in two separate player bases and return the repeats that exist
 * while keeping the time complexity under $O(N + M)
 *
 * Signature
 * vector<Player> sport1 & sport2 -> vector<Player> ListOfRepeatPlayers
 *
 *
 * Breakdown:
 * We can use a Hash-Table to allow us to have a O(N) add and lookup time,
 * this in turn allows us to try and add an entry. After adding our first list
 * we can add our second, anytime adding a player fails, we know that
 * player repeats. We can add them to an array and return them for the user.
 */
vector<Player> findRepeatPlayers( std::vector<Player> sport1 ,  std::vector<Player> sport2){
    // Creating a vector of players to hold our repeat players
    std::vector<Player> repeatPlayers;
    // Steps:
    // 1. Create a hash table to hold our players
    HashTable playerTable;
    // 2. Add our first set of players by looping through for each entry
    for(auto & counter : sport1)
    {
        playerTable.insertPlayer(counter.first_name + counter.last_name ,
                                 counter);
    }
    // 3. Add our second set of players
    for(auto & counter : sport2)
    {
        // If while after adding our second set of players we are given a number larger than 1,
        // then add that player to our repeat player base
        int numberOfPlayers = playerTable.insertPlayer(counter.first_name + counter.last_name ,
                                 counter);
        if(numberOfPlayers > 1) {
            // Adding that player to our list of repeat players
            repeatPlayers.push_back(counter);
        }
    }
    // Now returning that vector of players for the user
    return repeatPlayers;
};

int findMissingValue(int arr[] , int arraySize)
{
    // Looping through our entire array:
    // And keeping track of smallest
    int smallest = 0;
    // Largest
    int largest = 0;
    // and sum
    int sum = 0;
    for(int counter = 0 ; counter < arraySize ; counter++)
    {
        if(arr[counter] < smallest)
        {
            // Saving our new smallest
            smallest = arr[counter];
        }
        else if(arr[counter] > largest)
        {
            // Saving our largest
            largest = arr[counter];
        }
        // Adding to our sum
        sum += arr[counter];
    }
    // Now that we have our lower and upper bound we can find our expected sum
    int lowerSum = ((smallest * (smallest + 1)) /2);
    int higherSum = ((largest * (largest + 1)) / 2);
    // Calulating our expected sum
    return higherSum - lowerSum - sum;
}


//TODO Program 3, find the largest change
int findTheLargestChange(int arr[] , int arraySize){

    // Definging the three variables to keep track of our change
    int largestPrice = arr[0];
    int smallestprice = arr[0];
    int secondSmallestPrice = arr[0];

    // Looping for the length of our array
    for(int counter = 0 ; counter < arraySize ; counter++)
    {
        //If new max is larger than our current change it
        if(arr[counter] > largestPrice)
        {
            // Saving our new largestPrice
            largestPrice = arr[counter];
        }
        // If our new value will make our jump larger but only if we use the new value
        if( (largestPrice - smallestprice) < (arr[counter] - secondSmallestPrice))
        {
            // Updating oru smallest and largest price
            smallestprice = secondSmallestPrice;
            largestPrice = arr[counter];
        }
        // And if we find a price lower than our current minimum, hold it for later comparison
        if(arr[counter] < smallestprice)
        {
            // Holding our second-smallest price to keep track of for later
            secondSmallestPrice = arr[counter];
        }
    }
    return largestPrice - smallestprice;
}
//TODO Program 4: Largest of the 2 products in our array
int largestTwoNumberProduct(int arr[] , int arraySize){
    /* To find the two largest products within our array we can
     take the array we are given and keep track of the two highest
     values provided. To keep our time complexity O(N) we can just
     loop through the array once and use the absolute value to find
     the largest possible products
    */

    int largest = 0;
    int secondLargest = 0;
    // Looping for each entry
    for(int counter = 0; counter < arraySize ; counter++)
    {
        //If our current entry is larger than our largest make it our largest
        //and make our previous largest our second largest
        if(abs(arr[counter]) > abs(largest))
        {
            // Updating our second largest (Moving our largest down)
            secondLargest = largest;
            // Saving our newly found largest:
            largest = arr[counter];
        }
        else if(abs(arr[counter]) > abs(secondLargest))
        {
            // If it is only larger than our second largest, make it our second largest
            secondLargest = arr[counter];
        }
    }
    // Returning the product of our two found variables:
    return largest * secondLargest;
}

//TODO Sorting Patients Tempatures

double* sortPatientTempatures(double* arr , int arraySize)
{
    /*  Our input array of tempetures can only varry from 97 -99
     * with 1 possible decimal place, beacuse of this we can take in our value,
     * subtract 97 and then we only have a range from 0-20
     *
     * Now because we only have 20 possible entries it makes sense to use an algorithm
     * like counting sort, which will keep track of the number of our fixed entires,
     * then add them back correspoding with their occurance:
     *
     * In other words if we have 97.0 2 times, we would subtract 97, get array position 0,
     * increment that position as +2, then at the end add 2 97's back.
     */

    // Creating an array to hold our possible entries which is the number of possible
    // entires + 1
    int possibleTempatures[21] = {0};

    // Looping to count the number of times each entry exists
    for(int counter = 0; counter < arraySize; counter++ )
    {
        // Converting our tempature to our array position
        int bodyTempeture = round((arr[counter] * 10 ) - 970);

        // Incrementing at that array position
        possibleTempatures[bodyTempeture]++;
    }

    // Now that we know how many times they exist we can add them back:
    //Creating a variable to hold the tempeture we are currently adding back
    double currentTempature = 97.0;
    int currentPositonAddedBack = 0;
    //Looping for each entry within our array of possible entries
    for(int outterCounter = 0 ; outterCounter < 21 ; outterCounter++)
    {
        // If the entry at that position is greater than 0 then that tempature exists and we can add it back in
        if(possibleTempatures[outterCounter] > 0)
        {
            // Adding our current tempature to the array for the number of times we found it
            for(int innerCoutner = 0 ; innerCoutner < possibleTempatures[outterCounter] ; innerCoutner++)
            {
                // Adding our current entry
                arr[currentPositonAddedBack] = currentTempature;
                // Increasing the position of in the array that we should be adding to
                currentPositonAddedBack++;
            }
        }
        // If there is nothing at that position or we have already added that position,
        // increasing our tempature
         currentTempature += .1;
    }
// Returning our tempature array for the user:
return arr;

}

//TODO find the longest consecutive list of numbers within our array
int findLongestConsecutiveNumberStreak(int* arr , int arraySize)
{
    // Creating a variable to hold our longest streak of numbers
    int longestStreak = 0;
    // Creating a set so we can quickly compare our numbers
    set<int> set;
    // Adding all of our numbers to this set
    for(int counter = 0; counter < arraySize; counter++){
        set.insert(arr[counter]);
    }
    // Now that we have all of our numbers in the set we can start to look in
    // our array and see if our current entry is the "Beggining" of a set.
    // we can see this by always looking to the left as if we are the beginning
    // there would be no value next to us
    for(int Counter = 0; Counter < arraySize; Counter++){
        // Seeing if there exists in our set an item to the left of us
        if(set.find(arr[Counter] - 1) == set.end()){
            // if we can find somehting then we set the currentSetLength of this
            // set to 0 and keep searching
            int currentSetLength = 0;
            // Now for as long as we can keep finding items to the left
            // we can increase our currentLength
            while(set.find(arr[Counter] + currentSetLength) != set.end()){
                // If we do find somehting increasing our set length
                currentSetLength++;
            }
            if(currentSetLength > longestStreak){
                // If at any point our current set length is longer than our longest streak,
                // we will set that as our new longest steak:
                longestStreak = currentSetLength;
            }
        }
    }
    return longestStreak;
}







int main() {


    //TODO*****************************************************************************************************************
    // Prompt 1, seeing if we have repeat players:

    // Creating our Basket Ball Player List

    vector<Player> basketball_players = {
            {"Jill", "Huang", "Gators"},
            {"Janko", "Barton", "Sharks"},
            {"Wanda", "Vakulskas", "Sharks"},
            {"Jill", "Moloney", "Gators"},
            {"Luuk", "Watkins", "Gators"}
    };
    // Creating our List of Baseball Players
    std::vector<Player> baseball_players ={
            {"Hanzla",  "Radosti",  "32ers"},
            {"Tina",  "Watkins",  "Barleycorns"},
            {"Alex",  "Patel",  "32ers"},
            { "Jill",  "Huang",  "Barleycorns"},
            { "Wanda",  "Vakulskas",  "Barleycorns"}
    };

    std::vector<Player> repeatPlayers = findRepeatPlayers(basketball_players ,baseball_players);

    cout<< "Our Repeat Players are: " << endl;
    // Printing all of our found repeat Players
    for (auto & counter : repeatPlayers) {
        cout << counter.first_name << " " << counter.last_name <<endl;
    }


    //TODO*****************************************************************************************************************
    // Prompt 2: Find the Missing Integer

    //Creating an array to hold our possible numbers
    int arrayOfValues[] = {1 ,2,3,5,6};

    // Calling to find our missing value
    cout << "Expected Value is: " << findMissingValue(arrayOfValues , 5) << endl;
    // Calling our function to find our missing value:

    // Creating an array to hold our stock prices
    int stockPrices[] = {10, 7, 5, 8, 11, 2, 6};

    cout << "Our Largest Change is: " << findTheLargestChange(stockPrices , 7) << endl;


    //*******************************************************************************************************
    //TODO Program 4: Two largest product:
    // Creating an array of varibales
    int arrayOfPossibleProducts[] = {5, -10, -6, 9, 4};
    cout << "Our Largest Product is: " << largestTwoNumberProduct(arrayOfPossibleProducts , 5) << endl;
    std::cout << "Hello, World!" << std::endl;


    //*******************************************************************************************************
    //Program 5: Sort Patients Tempature
    // Creating an array of tempatures
    double arrayOfBodyTemps[] = {98.6, 98.0, 97.1, 99.0, 98.9, 97.8, 98.5, 98.2, 98.0, 97.1};
    // Printing our array before it's sorted
    for (int counter = 0; counter < 10 ; counter++) {
        cout<< arrayOfBodyTemps[counter] << endl;
    }
    // Printing our sorted Temperatures
    cout << "Printing our sorted Temperatures:" << endl;
     sortPatientTempatures(arrayOfBodyTemps , 10);
    for(int counter = 0; counter < 10 ; counter++) {
        cout<< arrayOfBodyTemps[counter] << endl;
    }

    //TODO Program 5: Longest consecutive streak of numbers:
    // Creating an array to hold our longest streak of numbers:
    int streakOfNumbers[] = {10, 5, 12, 3, 55, 30, 4, 11, 2};
    cout << "Our longest Steak of numbers is: " << findLongestConsecutiveNumberStreak(streakOfNumbers, 9);

    return 0;
}