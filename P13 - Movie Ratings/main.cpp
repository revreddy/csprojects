//
//  main.cpp
//  Project 13 - Movie Ratings
//      Uses a list of movies and reviews to comprile the top 10
//      movies by highest average rating and users by number of
//      ratings submitted. Then allow user to fetch the ratings
//      info for particular movies.
//
//  Created by Revanth Reddy on 2/1/15.
//  Language: C++
//  Envir: Windows 10, Visual Studios Community 2013 Update 4
//
//  Copyright (c) 2015 Revanth Reddy. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <iomanip>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::pair;
using std::setw;
using std::left;


//---------------------------------------------------------------------------------------------------------//
class Movie {
public:
	// Members //
	int movieID;
	string movieTitle;
	double avgRating;
	double totalRating;
	int nReviews;
	int nEachRating[5];

	// Constructor //
	Movie(int movie, string title) {
		movieID = movie;
		movieTitle = title;
		totalRating = 0.0;
		avgRating = 0.0;
		nReviews = 0;
		for (auto& x : nEachRating) {
			x = 0;
		}
	}
};


//---------------------------------------------------------------------------------------------------------//
class Review {
public:
	// Members //
	int movieID;
	int userID;
	int movieRating;

	// Constructor //
	Review(int movie, int user, int rating) {
		movieID = movie;
		userID = user;
		movieRating = rating;
	}
};


//---------------------------------------------------------------------------------------------------------//
// Display program information
void programInfo() {
    cout << endl;
    cout << "******************************" << endl;
    cout << "Author: Revanth Reddy" << endl;
    cout << "Project 13: Movie Ratings" << endl;
    cout << "******************************\n" << endl;
}

//---------------------------------------------------------------------------------------------------------//
// Parse one line of the movies file
// @return {Movie} - a new Movie object
Movie parseMovie(string line) {
	size_t pos = line.find(',');              // find position of comma
    
	string token = line.substr(0, pos);       // parse movieID
	int movieID = atoi(token.c_str());        // convert movieID to int
	string movieTitle = line.substr(pos + 1); // parse movieTitle
	
    return Movie(movieID, movieTitle);        // construct new movie object
                                              // and return to be stored in vector
}


//---------------------------------------------------------------------------------------------------------//
// Parse one line of the reviews file
// @return {Review} - a new Review object
Review parseReview(string line) {
	std::istringstream strstream(line);         // initilize stringstream
	string movieIDstr, userIDstr, ratingstr;    // create variables to store parsed data

	getline(strstream, movieIDstr, ',');        // parse movieID
	getline(strstream, userIDstr, ',');         // parse userID
	getline(strstream, ratingstr, ',');         // parse rating

	int movieID = atoi(movieIDstr.c_str());     // covert movieID from string to int
	int userID = atoi(userIDstr.c_str());       // covert userID from string to int
	int movieRating = atoi(ratingstr.c_str());  // covert rating from string to int
	return Review(movieID, userID, movieRating); // construct new review object
                                                 // and return to be stored in vector
}


//---------------------------------------------------------------------------------------------------------//
// Opens and reads movie file to create a vector of movie objects
// @param {vector<Movie>&} moviesVec - reference to vector to store movies
// @param {string} fName - name of file with the movies input data
void readMoviesFile(vector<Movie>& moviesVec, string fName) {
	cout << ">> Reading movies... ";
	std::ifstream mFile(fName.c_str());          // open movies file
	string s;
	while (getline(mFile, s)){                   // get each line of input from file
		moviesVec.push_back(parseMovie(s));      // parse line into a movie object
	};                                           // then add to end of vector
	cout << " " << moviesVec.size() << endl;     // display total number of movies parsed
}


//---------------------------------------------------------------------------------------------------------//
// Opens and reads movie file to create a vector of movie objects
// @param {vector<Review>&} reviewsVec - reference to reviews vector to store reviews data
// @param {string} fName - name of file with the review input data
void readReviewsFile(vector<Review>& reviewsVec, string fName) {
	cout << ">> Reading reviews... ";
	std::ifstream rFile(fName.c_str());
	std::istream_iterator<string> r_start(rFile), r_end;
    
	for_each(r_start, r_end, [&](string s) {        // for each line of file input
		reviewsVec.push_back(parseReview(s));       // parse line into a review object
	});                                             // then add to end of vector
	cout << " " << reviewsVec.size() << endl << endl; // display total number of reviews parsed
}


//---------------------------------------------------------------------------------------------------------//
// Transfer data for each review to respective movie, then calculates average rating
// @param {vector<Movie>&} moviesVec - reference to movies vector to store ratings data
//		for each respective movie
// @param {vector<Review>&} reviewsVec - reference to reviews vector to fetch review data
void computeMovieRatings(vector<Movie>& moviesVec, vector<Review>& reviewsVec) {
	for (Review& r : reviewsVec) {                      // for each review
		int i = r.movieID - 1;                          // calculate index

		moviesVec[i].totalRating += r.movieRating;      // add current review rating to total
		moviesVec[i].nReviews++;                        // increment number of reviews for that movie
		moviesVec[i].nEachRating[r.movieRating - 1]++;  // increment number 1,2,3,4,or 5's for that movie
	}

	for (Movie& m : moviesVec) {                        // for each movie
		m.avgRating = m.totalRating / m.nReviews;       // calculate the average rating
	}
}


//---------------------------------------------------------------------------------------------------------//
// Displays the Top 10 movies based on highest average rating
// @param {vector<Movie>&} moviesVec - reference to movies vector to store/fetch movie rating data
// @param {vector<Review>&} reviewsVec - reference to reviews vector to fetch review data
void displayTop10Movies(vector<Movie>& moviesVec, vector<Review>& reviewsVec){
	computeMovieRatings(moviesVec, reviewsVec);
	
	std::sort(moviesVec.begin(), moviesVec.end(), [](Movie& m1, Movie& m2) {
		return m1.avgRating > m2.avgRating;
	});

	cout << endl << ">> Top 10 Movies <<" << endl << endl;
	cout << setw(8) << std::left << "Rank";
	cout << setw(8) << "ID";
	cout << setw(8) << "Reviews";
	cout << setw(8) << "Avg";
	cout << "Name" << endl;

	for (int i = 0; i < 10; ++i) {
		cout << setw(8) << std::left << i + 1;
		cout << setw(8) << moviesVec[i].movieID;
		cout << setw(8) << moviesVec[i].nReviews;
		cout << setw(8) << moviesVec[i].avgRating;
		cout << "'" << moviesVec[i].movieTitle << "'" << endl;
	}
}


//---------------------------------------------------------------------------------------------------------//
// Count number of reviews written by each user, then sort in descending order
// @param {vector<Review>&} reviewsVec - reference to reviews vector to fetch review data
// @return {vector<pair<int, int> - returns the vector containing the userID and review counts
vector<pair<int, int>> countReviewsPerUser(vector<Review>& reviewsVec) {
	std::map<int, int> userMap;
	for (Review& r : reviewsVec) {
		userMap[r.userID]++;
	}

	vector<pair<int, int>> userVec(userMap.begin(), userMap.end());
	sort(userVec.begin(), userVec.end(), [](pair<int, int>& user1, pair<int, int>& user2){
		return user1.second > user2.second;  // sorting by number of reviews:
	});
	return userVec;
}


//---------------------------------------------------------------------------------------------------------//
// Displays the Top 10 users based on most number reviews written
// @param {vector<Review>&} reviewsVec - reference to reviews vector to fetch review data
void displayTop10Users(vector<Review>& reviewsVec){
	vector<pair<int, int>> userVec = countReviewsPerUser(reviewsVec);

	cout << endl << ">> Top 10 Users <<" << endl << endl
		<< setw(8) << left << "Rank"
		<< setw(8) << "ID"
		<< "Reviews" << endl;

	for (int i = 0; i < 10; ++i) {
		cout << setw(8) << left << i + 1;
		cout << setw(8) << userVec[i].first;
		cout << userVec[i].second << endl;
	}
}


//---------------------------------------------------------------------------------------------------------//
// Sorts the movies based on movieID then allows user to fetch single movie review data
// @param {vector<Movie>&} moviesVec - reference to movies vector to fetch review data
//		for the movie requested by user
void promptMovieInfo(vector<Movie>& moviesVec) {
	std::sort(moviesVec.begin(), moviesVec.end(), [](Movie& m1, Movie& m2) {
		return m1.movieID < m2.movieID;
	});

	size_t nMovies = moviesVec.size();
	int input;

	cout << endl << ">> Movie Information <<" << endl << endl;
	cout << "Please enter a movie ID [1.." << nMovies << "], 0 to exit:  ";
	std::cin >> input;

	while (input != 0) {
		if (input < 0 || input > nMovies)
			cout << "** Invalid movie id, please try again..." << endl;
		else {
			Movie m = moviesVec[input - 1];
			cout << endl;
			cout << setw(12) << left << "Movie:" << "'" << m.movieTitle << "'" << endl;
			cout << setw(13) << left << "Avg rating:" << m.avgRating << endl;
			cout << setw(13) << left << "Num reviews:" << m.nReviews << endl;
			cout << setw(13) << left << "Num 1's:" << m.nEachRating[0] << endl;
			cout << setw(13) << left << "Num 2's:" << m.nEachRating[1] << endl;
			cout << setw(13) << left << "Num 3's:" << m.nEachRating[2] << endl;
			cout << setw(13) << left << "Num 4's:" << m.nEachRating[3] << endl;
			cout << setw(13) << left << "Num 5's:" << m.nEachRating[4] << endl << endl;
		}

		cout << "Please enter a movie ID [1.." << nMovies << "], 0 to exit:  ";
		std::cin >> input;
	}
    cout << endl;
}



//---------------------------------------------------------------------------------------------------------//
int main(int argc, const char *argv[]) {
    programInfo();
    
    // Read and store list of movies
	vector<Movie> moviesVec;
	readMoviesFile(moviesVec, "movies.txt"); // ** USE TO CHANGE MOVIES FILE NAME **
	
	// Read and store all reviews
	vector<Review> reviewsVec;
	readReviewsFile(reviewsVec, "reviews.txt"); // ** USE TO CHANGE REVIEW FILE NAME **

	// Compute and display top 10 movies and reviewers
	displayTop10Movies(moviesVec, reviewsVec);
	displayTop10Users(reviewsVec);

	// Allow user to fetch review data for particular movie
	promptMovieInfo(moviesVec);

	cout << "Done" << endl;

	return 0;
}
