//
// Jacob Janowski
// U. of Illinois, Chicago
// CS 251: Fall 2019
//
// Project #02: inputs movies and reviews, allowing the user to search
// by movie ID, movie Name, or review ID.  Uses binary search trees for 
// fast search; no other data structures are allowed.
//

#include <iostream>
#include <fstream>
#include <string>
#include "bst.h"

using namespace std;


	struct MovieData {
		string movieTitle;
		int IDnumber;
		int pubYear;
		int rating    = 0;
		int num5Stars = 0;
		int num4Stars = 0;
		int num3Stars = 0;
		int num2Stars = 0;
		int num1Stars = 0;
	};

//
// trim
//
// trims whitespace from beginning and end of string.
//
// Ref: https://stackoverflow.com/questions/25829143/trim-whitespace-from-a-string
// Modified: to handle empty strings, and strings of all blanks.
//
string trim(const string& str)
{
	size_t first = str.find_first_not_of(" \t\n\r");
	size_t last = str.find_last_not_of(" \t\n\r");

	if (first == string::npos && last == string::npos)  // empty, or all blanks:
		return "";
	else if (first == string::npos)  // no blanks at the start:
		first = 0;                     // 0-based
	else if (last == string::npos)   // no blanks trailing at end:
		last = str.length() - 1;       // 0-based

	return str.substr(first, (last - first + 1));
}


//
// InputReviews
//
// In here, we pass in the reviews1.txt and search for either 
// the id value or the name of the movie.

void InputReviews(string reviewsFilename ,binarysearchtree<int,MovieData>&bstMoviesByID,  
										  binarysearchtree<string,MovieData>&movieNames) {

											  
	ifstream reviewsFile(reviewsFilename);
	int 	id, IDval;
	int     rating = 0;     
	int     reviewsCount = 0;
	if (!reviewsFile.good())
	{
		cout << "**Error: unable to open movies file '" << reviewsFilename << "', exiting" << endl;
		return;
	}

	reviewsFile >> IDval;       //read in fileName

	while (!reviewsFile.eof())
	{
		//read in the id and rating.
		reviewsFile >> 	id;
		reviewsFile >> rating;
	
        // Search by movie name inside the moviesByID bst and set
        // the rating to the corresponding numStars.	
		MovieData* myData = bstMoviesByID.search(id);
        MovieData* titleData = movieNames.search(myData->movieTitle);

        switch(rating) {
            case 1: (myData->num1Stars)++;
            break;
            case 2: (myData->num2Stars)++;
            break;
            case 3: (myData->num3Stars)++;
            break;
            case 4: (myData->num4Stars)++;
            break;
            case 5: (myData->num5Stars)++;
            break;
        }
	
        // Search by movie name inside the movieNames bst and set
        // the rating to the corresponding numStars.
        switch(rating) {
            case 1: (titleData->num1Stars)++;
            break;
            case 2: (titleData->num2Stars)++;
            break;
            case 3: (titleData->num3Stars)++;
            break;
            case 4: (titleData->num4Stars)++;
            break;
            case 5: (titleData->num5Stars)++;
            break;
        }		


		reviewsCount++;
		reviewsFile >> IDval;
	}						  
	cout << "Num reviews: " << reviewsCount << endl << endl;

}
//
// InputMovies
//
// In here, we take the data from the movies file.

void InputMovies(string moviesFilename, 
                binarysearchtree<int,MovieData> &bstMoviesByID, 
                binarysearchtree<string,MovieData> &movieNames){

	ifstream moviesFile(moviesFilename);
	
	int      id, pubYear, rating;
	int 	 movieCount = 0;
	string   name;
	MovieData IDnode;   


	if (!moviesFile.good())
	{
		cout << "**Error: unable to open movies file '" << moviesFilename << "', exiting" << endl;
		return;
	}

	moviesFile >> id;  // get first ID, or set EOF flag if file empty:

	while (!moviesFile.eof())
	{
		// we have more data, so input publication year and movie name:
		moviesFile >> pubYear;
		getline(moviesFile, name);  // movie name fills rest of input line:
		name = trim(name);
        movieCount++;
        
        // set the values and insert data.
		IDnode.pubYear = pubYear;       
		IDnode.IDnumber = id;
		IDnode.movieTitle = name;
		bstMoviesByID.insert(id, IDnode);   
        movieNames.insert(name, IDnode);


		
		moviesFile >> id;  // get next ID, or set EOF flag if no more data:		
		
	}
	cout << "Num movies: " << movieCount << endl;


}

// Pass in a pointer of the value we have 
// and add up all of the movies values by their ratings.
// return the avg.
double average(MovieData *info) {
	double stars = (info->num1Stars) * 1 + 
                     (info->num2Stars) * 2 + 
                     (info->num3Stars) * 3 +
                     (info->num4Stars) * 4 + 
                     (info->num5Stars) * 5;
    if(stars != 0) {
	double total = stars / (info->num1Stars + 
                                    info->num2Stars + 
                                    info->num3Stars + 
                                    info->num4Stars + 
                                    info->num5Stars);
                                    return total;
    }
	
}


// checks if user input is string or number:
// return true if string, false if number.
bool checkInput(string&str) {
	int i;
	int titleLength = str.length();
	for(i = 0; i < titleLength; i++) {
        if(isalpha(str[i])) {
            return true;
        }
    }
	return false;

    
}
// This funciton will pass in both trees as well as the user's choice.
// Depending on what the user enters, we will search the ID tree or the Name tree.

void printInfo(string choice, binarysearchtree<int,MovieData>&bstMoviesByID,binarysearchtree<string,MovieData>&movieNames) {
    
    // create pointer to refer back.
    // While the user doesn't put in sentinel value, proceed.
    int userChoice;
    MovieData *resultNode;
        
		 
		// this statement executes if the user input 
        // is a string value; so search by movie title.
		if (checkInput(choice)) {

			resultNode = movieNames.search(choice);

			if(resultNode != nullptr) {
                cout << "Movie ID: " << resultNode->IDnumber << endl;
				cout << "Movie Name: " << choice << endl;
				cout << "Avg rating: " << average(resultNode) << endl;
				cout << "5 stars: " << resultNode->num5Stars << endl;
				cout << "4 stars: " << resultNode->num4Stars << endl;
				cout << "3 stars: " << resultNode->num3Stars << endl;
				cout << "2 stars: " << resultNode->num2Stars << endl;
				cout << "1 star: " << resultNode->num1Stars << endl << endl;

			} else {
				
                cout << "not found..." << endl << endl;

			}
        // this statement executes if the user input
        // is a string value; so search by movie ID.
		} else  {
			userChoice = stoi(choice);      //use stoi
			resultNode = bstMoviesByID.search(userChoice);
            
				if(resultNode != nullptr) {
                    cout << "Movie ID: " << userChoice << endl;
					cout << "Movie Name: " << resultNode->movieTitle << endl;
					cout << "Avg rating: " << average(resultNode) << endl;
					cout << "5 stars: " << resultNode->num5Stars << endl;
					cout << "4 stars: " << resultNode->num4Stars << endl;
					cout << "3 stars: " << resultNode->num3Stars << endl;
					cout << "2 stars: " << resultNode->num2Stars << endl;
					cout << "1 star: " << resultNode->num1Stars << endl << endl;

				} else {
				    cout << "not found..." << endl << endl;

				}
			}
	
        cout << "Enter a movie id or name (or # to quit)> ";
		
}
int main()
{
	
	binarysearchtree<int, MovieData> bstMoviesByID;
	binarysearchtree<string, MovieData> movieNames;
	string moviesFilename; // = "movies1.txt";
	string reviewsFilename; // = "reviews1.txt";
	string choice;
	


	cout << "movies file?> ";
	cin >> moviesFilename;

	cout << "reviews file?> ";
	cin >> reviewsFilename;

	string junk;
	getline(cin, junk);  // discard EOL following last input:
	InputMovies(moviesFilename, bstMoviesByID, movieNames);
	InputReviews(reviewsFilename, bstMoviesByID, movieNames);
	


	cout << "Tree by movie id: size=" << bstMoviesByID.size()<< ", height=" << bstMoviesByID.height() << endl;
	cout << "Tree by movie name: size=" <<movieNames.size() << ", height=" << movieNames.height() << endl << endl;

	cout << "Enter a movie id or name (or # to quit)> ";
	getline(cin,choice);
    while (choice != "#") {
        	printInfo(choice,bstMoviesByID, movieNames);
            getline(cin,choice);
    }


	// done:
	return 0;
}