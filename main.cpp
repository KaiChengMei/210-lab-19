// COMSC-210 | Lab 19 | Kai-Cheng Mei

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

struct ReviewNode {

    double rating;
    string comment;
    ReviewNode *next;
};

class Movie {
        
    private:

        string title;
        ReviewNode *head;

    public:

        Movie(string movieTitle) : title(movieTitle), head(nullptr) {}

        void addReview(double rating, const string &comment) {
            ReviewNode *newNode = new ReviewNode{rating, comment, head};
            head = newNode;
        }

        void printReviews() const {

            ReviewNode *current = head;
            int count = 0;
            double sum = 0.0;

            // Review: rate: comments
            cout << "Movie: " << title <<endl;
            while (current) {
                cout << "> Review #" << count + 1 << ": " <<current->rating
                    << ": " << current->comment <<endl;
                sum += current->rating;
                current = current->next;
                count++;
            }

            if (count > 0)  {
                cout << "* Average Rating: " << sum / count<<endl;
            }
        }
};

int main() {

    srand(time(0)); 

    // read file
    ifstream file("review.txt");
    if (!file) {
        cout << "Error: Cannot open reviews.txt!" << endl;
        return 1;
    }
    vector<Movie> movies;
    string line;
    int movieCount = 0;

    while (getline(file, line)) {
        Movie movie(line);  //title

        for (int i = 0; i < 3; i++) {  // Each 3 reviews
            string comment;
            getline(file, comment);
            double rating = 1.0 + (rand() % 50) / 10.0;  // Random rating
            movie.addReview(rating, comment);
        }

        movies.push_back(movie);
        movieCount++ ;
    }

    // Output
    for (const auto &movie : movies) {
        movie.printReviews();
        cout <<endl;
    }

    file.close();
    return 0;
}