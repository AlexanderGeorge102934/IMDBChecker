
#include <iostream>
#include <cctype>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include<bits/stdc++.h>


using namespace std;





/*********************************************** Helper functions ***************************************/

//The splitString function takes a line and split it on the delimiter and push the parts into items
void splitString(string line, char delimiter, vector<string> &items) {
    stringstream s_stream(line);
    while (s_stream.good()) {
        string item;
        getline(s_stream, item, delimiter);
        items.push_back(item);
    }

}


/**********************************************************************************************************/


//Takes input string and outputs lower case version of string
string toLower(string normalString) {
    string stringTemp = "";
    for (int i = 0; i < normalString.size(); i++) {
        if (isalpha(normalString.at(i))) {
            stringTemp += tolower(normalString.at(i));
        } else {
            stringTemp += normalString.at(i);
        }
    }
    return stringTemp;
}


//takes in a string and returns a string that gets rid of commas in string
string ridOfComma(string GenreString) {
    replace(GenreString.begin(), GenreString.end(), ',', ' '); // replace all 'x' to 'y'
    return GenreString;
}

//Struct with 4 values titleid, startyear, primarytitle, genres
struct TitleRecord {
    string titleID;
    string startYear;
    string primaryTitle;
    string genres;
};

//Struct with 5 values nameid, primaryName, birthYear, deathYear, primaryProfession
struct NameRecord {
    string nameID;
    string primaryName;
    string birthYear;
    string deathYear;
    string primaryProfession;
};


//Struct with 3 values titleID, nameID, character
struct PrincipleRecord {
    string titleID;
    string nameID;
    string character;
};


//Takes in the input of a movie that has '+' seperating each word and outputs a vector that contains each word that was split by '+'
vector<string> movieInputVector(string inputMovie) {
    vector<string> inputMovieVector;
    splitString(inputMovie, '+', inputMovieVector);
    return inputMovieVector;


};


//Takes in the input of an actor name that has '+' seperating each word and outputs a vector that contains each word that was split by '+'
vector<string> actorInputVector(string inputActor) {
    vector<string> inputActorVector;
    splitString(inputActor, '+', inputActorVector);
    return inputActorVector;
}


// reads all lines in the principle records saving them into a vector
vector<PrincipleRecord> readAllLinesPrinciples(string fileName) {
    ifstream file(fileName);
    string line;
    struct PrincipleRecord principleRecord;
    int i = 0;
    getline(file, line);
    vector<PrincipleRecord> finalList;
    while (getline(file, line)) {
        vector<string> fileVector;
        splitString(line, '\t', fileVector);
        principleRecord.titleID = fileVector.at(0);
        principleRecord.nameID = fileVector.at(2);
        principleRecord.character = fileVector.at(5);
        finalList.push_back(principleRecord);
    }
    file.close();

    return finalList;


}

//Finds movies in vector containing structs of titles files and sees if any of those title record vectors primary titles holds the name of the input movie and then puts the movies that have a match into a vector
vector<TitleRecord> searchMovietoActor(vector<string> movieTitle, vector<TitleRecord> titleRecord) {
    vector<string> listOfMatchedMoviesID;
    vector<string> nameRecord;
    vector<string> listOfmatchedMovieNamesTitles;
    vector<string> listOfMatchedMoviesGenre;
    vector<string> listOfMatchedMoviesYear;
    vector<TitleRecord> vectorofMatchedMovies;

    for (int i = 0; i < titleRecord.size(); i++) {
        bool statementCondition = true;
        for (int p = 0; p < movieTitle.size(); p++) {
            if (toLower(titleRecord.at(i).primaryTitle).find(movieTitle.at(p)) != string::npos) {
                continue;
            } else {
                statementCondition = false;
                break;
            }


        }

        if (statementCondition == true) {
            vectorofMatchedMovies.push_back(titleRecord.at(i));
            listOfMatchedMoviesID.push_back(titleRecord.at(i).titleID);
            listOfmatchedMovieNamesTitles.push_back(titleRecord.at(i).primaryTitle);
            listOfMatchedMoviesGenre.push_back(titleRecord.at(i).genres);
            listOfMatchedMoviesYear.push_back(titleRecord.at(i).startYear);
        }

    }
    if (listOfmatchedMovieNamesTitles.size() != 0) {
        for (int l = 0; l < listOfmatchedMovieNamesTitles.size(); l++) {
            cout << l << ": " << endl;
            cout << listOfmatchedMovieNamesTitles.at(l) << endl;
            cout << "Year: " << listOfMatchedMoviesYear.at(l) << endl;
            cout << "Genre: " << ridOfComma(listOfMatchedMoviesGenre.at(l)) << endl;
            cout << "---------------" << endl;


        }
    } else {
        cout << "No match found!" << endl;
        return vectorofMatchedMovies;

    }
    return vectorofMatchedMovies;
}

//Finds actors in vector containing structs of names files and sees if any of those name record vectors primary names holds the name of the input actor name and then puts the movies that have a match into a vector
vector<NameRecord> searchActortoMovie(vector<string> ActorName, vector<NameRecord> nameRecord, string filePrincipals) {
    vector<string> matchedActorsName;
    vector<string> ActorsPrimaryProfession;
    vector<string> ActorsBirthYear;
    vector<string> ActorsDeathYear;
    vector<NameRecord> ActorNumID;

    for (int i = 0; i < nameRecord.size(); i++) {
        bool statementCondition = true;
        for (int j = 0; j < ActorName.size(); j++) {
            if (toLower(nameRecord.at(i).primaryName).find(ActorName.at(j)) != string::npos) {
                continue;
            } else {
                statementCondition = false;
                break;
            }
        }
        if (statementCondition == true) {
            matchedActorsName.push_back(nameRecord.at(i).primaryName);
            ActorsPrimaryProfession.push_back(nameRecord.at(i).primaryProfession);
            ActorsBirthYear.push_back(nameRecord.at(i).birthYear);
            ActorsDeathYear.push_back(nameRecord.at(i).deathYear);
            ActorNumID.push_back(nameRecord.at(i));


        }

    }
    if (matchedActorsName.size() > 0) {
        for (int l = 0; l < matchedActorsName.size(); l++) {
            cout << l << ": " << endl;
            cout << matchedActorsName.at(l) << endl;
            cout << ActorsPrimaryProfession.at(l) << endl;
            cout << "(" << ActorsBirthYear.at(l) << "-" << ActorsDeathYear.at(l) << ")" << endl;
            cout << "---------------" << endl;
        }
    }

    return ActorNumID;


}


// reads all lines in movies.titles and stores them into a struct type vector
vector<TitleRecord> readAllLinesTitles(string fileName) {
    ifstream file(fileName);
    string line;
    struct TitleRecord titleRecord;
    int i = 0;
    getline(file, line);
    vector<TitleRecord> finalList;
    while (getline(file, line)) {
        vector<string> fileVector;
        splitString(line, '\t', fileVector);
        titleRecord.titleID = fileVector.at(0);
        titleRecord.startYear = fileVector.at(5);
        titleRecord.primaryTitle = fileVector.at(2);
        titleRecord.genres = fileVector.at(8);
        finalList.push_back(titleRecord);


    }
    file.close();

    return finalList;


}

//reads all lines in name.titles and puts the file into a struct type vector
vector<NameRecord> readAllLinesNames(string fileName) {
    ifstream file(fileName);
    string line;
    struct NameRecord nameRecord;
    int i = 0;
    getline(file, line);
    vector<NameRecord> finalList;
    while (getline(file, line)) {
        vector<string> fileVector;
        splitString(line, '\t', fileVector);
        nameRecord.birthYear = fileVector.at(2);
        nameRecord.deathYear = fileVector.at(3);
        nameRecord.nameID = fileVector.at(0);
        nameRecord.primaryName = fileVector.at(1);
        nameRecord.primaryProfession = fileVector.at(4);
        finalList.push_back(nameRecord);
    }
    file.close();

    return finalList;


}

//Takes in a title id argument and sees if that title id matches with any vectors title ids in the principle file and gets the name id from that vector and puts it into a vector
vector<string> getnameIdfromprincipleRecord(string titleID, string fileName) {
    vector<PrincipleRecord> princpleRecord = readAllLinesPrinciples(fileName);
    vector<string> nameRecord;
    vector<string> listofCharacterActorPlayed;
    for (int i = 0; i < princpleRecord.size(); i++) {
        if (titleID == princpleRecord.at(i).titleID) {
            nameRecord.push_back(princpleRecord.at(i).nameID);
        }
    }
    return nameRecord;

}


//Takes in a name id argument and sees if that name id matches with any vectors name ids in the principle file and gets the title id from that vector and puts it into a vector
vector<string> getMovieIdfromprincipleRecord(string nameID, string fileName) {
    vector<PrincipleRecord> principleRecord = readAllLinesPrinciples(fileName);
    vector<string> titleID;
    for (int i = 0; i < principleRecord.size(); i++) {
        if (nameID == principleRecord.at(i).nameID) {
            titleID.push_back(principleRecord.at(i).titleID);
        }
    }

    return titleID;

}


//Gets characters of matching Actor from principle record for option 1
vector<string> getcharacterfromPrincipleRecord1(string titleID, string fileName) {
    vector<PrincipleRecord> princpleRecord = readAllLinesPrinciples(fileName);
    vector<string> listofCharacterActorPlayed;
    for (int i = 0; i < princpleRecord.size(); i++) {
        if (titleID == princpleRecord.at(i).titleID) {
            listofCharacterActorPlayed.push_back((princpleRecord.at(i).character)); //Need to save this list for another
        }
    }
    return listofCharacterActorPlayed;

}

//Gets characters of matching Actor from principle record for option 2
vector<string> getcharacterfromPrincipleRecord2(string nameID, string fileName) {
    vector<PrincipleRecord> princpleRecord = readAllLinesPrinciples(fileName);
    vector<string> listofCharacterActorPlayed;
    for (int i = 0; i < princpleRecord.size(); i++) {
        if (nameID == princpleRecord.at(i).nameID) {
            listofCharacterActorPlayed.push_back((princpleRecord.at(i).character));
        }
    }
    return listofCharacterActorPlayed;

}

//Outputs the actors name and character they played in the movie
void getActors(vector<string> listofnameID, vector<string> listofCharactersPlayedbyActor, string fileName) {
    vector<NameRecord> nameRecord = readAllLinesNames(fileName);
    for (int i = 0; i < nameRecord.size(); i++) {
        for (int j = 0; j < listofnameID.size(); j++) {
            if (listofnameID.at(j) == nameRecord.at(i).nameID) {
                if (listofCharactersPlayedbyActor.at(j) != "\\N") {
                    cout << nameRecord.at(i).primaryName << " " << listofCharactersPlayedbyActor.at(j) << endl;
                }

            }
        }
    }


}

//Returns vector of matched year of movie 
vector<string> listOfMatchedYearofMovie (string fileName, vector<string> listofMatchedMovieID){
    vector<TitleRecord> titleRecord;
    titleRecord=readAllLinesTitles(fileName);
    vector<string> matchedMovieYear;
    for (int i=0; i< titleRecord.size(); i++){
        for (int j =0; j<listofMatchedMovieID.size(); j++){
            if(listofMatchedMovieID.at(j)==titleRecord.at(i).titleID){
                matchedMovieYear.push_back(titleRecord.at(i).startYear);
            }
        }
    }
    return matchedMovieYear;

}



//Outputs movies the actor has played along with the character they played in that corresponding movie
void getMovie(vector<string> listofTitleId, vector<string> listofCharactersPlayedbyActor, string fileName, vector<string> listOfMatchedMovieYear) {
    vector<TitleRecord> titleRecord = readAllLinesTitles(fileName);
    for (int i = 0; i < titleRecord.size(); i++) {
        for (int j = 0; j < listofTitleId.size(); j++) {
            if (listofTitleId.at(j) == titleRecord.at(i).titleID) {
                if (listofCharactersPlayedbyActor.at(j) != "\\N") {
                    cout << titleRecord.at(i).primaryTitle << " " << listOfMatchedMovieYear.at(j) << " " << listofCharactersPlayedbyActor.at(j) << endl;
                }
            }
        }
    }
}


//Outputs the menu input and calls other functions to search for movies and actors as well as actors that participated in the movies and movies that actor participated based on the input given and exits if 3 is called
void MenuInput(string titlesFile, string namesFile, string principalsFile) {

    int menuOptionNumber;
    cout << "Select a menu option: " << endl;
    cout << "    1. Search for a movie" << endl;
    cout << "    2. Search for actors/actresses" << endl;
    cout << "    3. Exit" << endl;
    cout << "Your choice --> ";
    cin >> menuOptionNumber;
    if (menuOptionNumber == 1) {
        int secondUserInput;
        string inputMovie;
        vector<TitleRecord> vectorWithMatchedMovies;
        cout << "Enter search phrase: " << endl;
        cin >> inputMovie;
        cout << "---------------" << endl;
        inputMovie = toLower(inputMovie);
        vector<string> inputMovieVector = movieInputVector(inputMovie);
        vector<TitleRecord> titleRecordVector = readAllLinesTitles(titlesFile);
        vectorWithMatchedMovies = searchMovietoActor(inputMovieVector, titleRecordVector);
        if (vectorWithMatchedMovies.size() != 0) {
            cout << "Select a movie to see its actors/actresses (-1 to go back to the previous menu): ";
            cin >> secondUserInput;
            if (secondUserInput == -1) {
                MenuInput(titlesFile, namesFile, principalsFile);
            }
            vector<string> listofmatchedNameIDs;
            vector<string> listofmatchedCharacters;
            listofmatchedNameIDs = getnameIdfromprincipleRecord(vectorWithMatchedMovies.at(secondUserInput).titleID,
                                                                principalsFile);
            listofmatchedCharacters = getcharacterfromPrincipleRecord1(
                    vectorWithMatchedMovies.at(secondUserInput).titleID, principalsFile);
            getActors(listofmatchedNameIDs, listofmatchedCharacters, namesFile);
        }


    }
    else if (menuOptionNumber == 2) {
        int secondUserInput;
        string inputActor;
        cout << "Enter search phrase: " << endl;
        cin >> inputActor;
        inputActor = toLower(inputActor);
        while(inputActor!="done") {
            cout << "---------------" << endl;
            vector<string> inputActorVector = actorInputVector(inputActor); //Puts input into vector
            vector<NameRecord> nameRecord = readAllLinesNames(
                    namesFile); // reads all lines of names file and stores in vector
            vector<NameRecord> matchednameIDofActor;
            matchednameIDofActor = searchActortoMovie(inputActorVector, nameRecord,
                                                      principalsFile); //Stores matched actors into vector
            cout << "Select an actor/actress to see movies(-1 to go back to the previous menu): ";
            cin >> secondUserInput;
            if (secondUserInput == -1) {
                MenuInput(titlesFile, namesFile, principalsFile);
            }
            vector<string> listofmatchedMovieID;
            vector<string> listofmatchedCharacters = getcharacterfromPrincipleRecord2(
                    matchednameIDofActor.at(secondUserInput).nameID, principalsFile);
            listofmatchedMovieID = getMovieIdfromprincipleRecord(matchednameIDofActor.at(secondUserInput).nameID,
                                                                 principalsFile);
            vector<string> matchedMovieYearlist=listOfMatchedYearofMovie(titlesFile, listofmatchedMovieID);
            getMovie(listofmatchedMovieID, listofmatchedCharacters, titlesFile, matchedMovieYearlist);
            cout << "Enter search phrase (type done to go back to the previous menu): " << endl;
            cin >> inputActor;
            inputActor=toLower(inputActor);
        }
        if (inputActor=="done"){
            MenuInput(titlesFile, namesFile, principalsFile);
        }
    }
    else if(menuOptionNumber==3){

    }

}

//Runs menu input function
int run(string titlesFile, string namesFile, string principalsFile) {
    MenuInput(titlesFile, namesFile, principalsFile);
    return 0;
}

int main() {
    //Change these addresses according to your local machine
    string titlesFile = "movie.titles.tsv";
    string namesFile = "movie.names.tsv";
    string principalsFile = "movie.principals.tsv";
    //DO NOT change the main function. The main function will be removed by the autograder
    run(titlesFile, namesFile, principalsFile);
    return 0;
}
