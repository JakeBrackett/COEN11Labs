//
//  quiz4.c
//  
//
//  Created by Jacob Brackett
//  Student ID: W0976434

//Create a structure that keeps info for movies. For each movie we have the title, a pointer to a struct actors/actresses (array of up to five actors/actresses), the year, the rating and the director. Each actor/actress is a structure that has first name, last name, year of first movie and age. Create a complete program that shows the content of an array of three movies. Make sure to fill this array with your three favorite movies.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct actor{
    char first_name[100];
    char last_name[100];
    int first_movie_year;
    int age;
};

struct movie{
    char title[100];
    struct actor actors[5];
    int year;
    char rating[7];
    char director[50];
};

int main(){
    int i, j;
    
    struct movie best_movies[3];
    struct actor christian_bale = {"Christian", "Bale", 1982, 33};
    struct actor morgan_freeman = {"Morgan", "Freeman", 1972, 42};
    struct actor anne = {"Anne", "Hathaway", 1982, 32};
    
    strcpy(best_movies[0].title,  "The Dark Knight");
    best_movies[0].actors[0] = christian_bale;
    best_movies[0].actors[1] = morgan_freeman;
    best_movies[0].year = 2013;
    strcpy(best_movies[0].rating, "PG-13");
    strcpy(best_movies[0].director, "Christopher Nolan");
    
    strcpy(best_movies[1].title, "Batman Begins");
    best_movies[1].actors[0] = christian_bale;
    best_movies[1].actors[1] = morgan_freeman;
    best_movies[1].year = 2012;
    strcpy(best_movies[1].rating, "PG-13");
    strcpy(best_movies[1].director, "Christopher Nolan");
    
    strcpy(best_movies[2].title, "The Dark Knight Rises");
    best_movies[2].actors[0] = christian_bale;
    best_movies[2].actors[1] = anne;
    best_movies[2].year = 2014;
    strcpy(best_movies[2].rating, "PG-13");
    strcpy(best_movies[2].director, "Christopher Nolan");
    
    for(i = 0; i < 3; i++){
        printf("%s. Made in %d, rated %s. Directed by %s.\n", best_movies[i].title, best_movies[i].year, best_movies[i].rating, best_movies[i].director);
        printf("Actors: \n");
        for(j = 0; j < 2; j++){
            printf("%s %s. First movie was in %d. They are currently %d years old.\n", best_movies[i].actors[j].first_name, best_movies[i].actors[j].last_name, best_movies[i].actors[j].first_movie_year, best_movies[i].actors[j].age);
        }
        printf("\n\n");
    }
}
