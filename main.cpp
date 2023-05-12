#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <cctype>
#include<limits>
#include <algorithm>

using namespace std;

//the song class
class Song{
  private:
    int year;
    int month;
    int day;
    int rank;
    int lastrank;
    int peakrank;
    int weeksonboard;
    string title;
    string artist;

  public:
    //default contructor
    Song(){
      year = -1;
      month = -1;
      day = -1;
      rank = -1;
      lastrank = -1;
      peakrank = -1;
      weeksonboard = -1;
      title = "(NO_TITLE)";
      artist = "(NO_ARTIST)";
    }

    //fully qualified constructor
    Song(int month, int day, int year, int rank, string title, string artist, int peakrank, int weeksonboard){
      
      setyear(year);
      setmonth(month);
      setday(day);
      setrank(rank);
      setlastrank(-1);
      setpeakrank(peakrank);
      setweeksonboard(weeksonboard);
      settitle(title);
      setartist(artist);
    }

    Song(int month, int day, int year, int rank, string title, string artist, int lastrank, int peakrank, int weeksonboard){
      
      setyear(year);
      setmonth(month);
      setday(day);
      setrank(rank);
      setlastrank(lastrank);
      setpeakrank(peakrank);
      setweeksonboard(weeksonboard);
      settitle(title);
      setartist(artist);
    }


    //the setter methods
    void setyear(int year){
      this->year = year;
    }
    void setmonth(int month){
      this->month = month;
    }
    void setday(int day){
      this->day = day;
    }
    void setrank(int rank){
      this->rank = rank;
    }
    void setlastrank(int lastrank){
      this->lastrank = lastrank;
    }
    void setpeakrank(int peakrank){
      this->peakrank = peakrank;
    }
    void setweeksonboard(int weeksonboard){
      this->weeksonboard = weeksonboard;
    }
    void settitle(string title){
      this->title = title;
    }
    void setartist(string artist){
      this->artist = artist;
    }

    //the getter mothods
    int getyear(){
      return year;
    }
    int getmonth(){
      return month;
    }
    int getday(){
      return day;
    }
    int getrank(){
      return rank;
    }
    int getlastrank(){
      return lastrank;
    }
    int getpeakrank(){
      return peakrank;
    }
    int getweeksonboard(){
      return weeksonboard;
    }
    string gettitle(){
      return title;
    }
    string getartist(){
      return artist;
    }
};


//to read in the data
void charts(vector<Song> &data, int menuop){
  
  string values[9];
  int valuez[9];
  ifstream stream;
  if(menuop == 1){
    stream.open("charts_top50_1960_1980.csv");
    assert(stream.fail() == false);
    data.clear();
  }
  else if(menuop == 2){
    stream.open("charts_top50_1981_2000.csv");
    assert(stream.fail() == false);
    data.clear();
  }
  else if(menuop == 3){
    stream.open("charts_top50_2001_2020.csv");
    assert(stream.fail() == false);
    data.clear();
  }
  string tempstring;
  int counter;
  getline(stream, tempstring);
  while(getline(stream, tempstring)){
    counter = 0;
    for(int i = 0; i < tempstring.length(); i++){
      if(counter == 2){
        break;
      }
      if(tempstring[i] == '/'){
        tempstring.replace(i, 1, ",");
        counter++;
      }
    }
    int start = 0;
    for(int i = 0; i < 9; i++){
      int index = tempstring.find(',');
      string news = tempstring.substr(start, index);
      values[i] = news;
      tempstring.erase(start, index+1);
      stringstream ss;
      ss << values[i];
      ss >> valuez[i];
    }

    if(values[6].length() < 1){
      Song tempsong(valuez[0], valuez[1], valuez[2], valuez[3], values[4], values[5], valuez[7], valuez[8]);
      data.push_back(tempsong);
    }
    else{
      Song tempsong(valuez[0], valuez[1], valuez[2], valuez[3], values[4], values[5], valuez[6], valuez[7], valuez[8]);
      data.push_back(tempsong);
    }
    
  }
  stream.close();
}


//unique song counter
void numberofsongs(vector<Song> &songs, int mode){
  vector<string> uniques(0);
  bool isFound= false;
  for(int i = 0; i < songs.size() ; i++){
    
    isFound = false;
    for(int j = 0; j < uniques.size(); j++){
      if(songs.at(i).gettitle() == uniques.at(j)  )    {

        isFound = true;
        break;
      }
    }
    if(!isFound){
      uniques.push_back(songs.at(i).gettitle());
    }
  }

  cout << "Total number of rows: " << songs.size() << "\nNumber of unique songs represented in the dataset: " << uniques.size() << endl;

}

//finding the most popular song
void popsong(vector<Song> &songs, char mode, int year){
  int highest, temphighest;
  highest = -1;
  vector<Song> temp;
  mode = toupper(mode);
  if(cin.fail()){
    cin.clear();
    cin.ignore(1000, '\n');
    return;
  }
  else if(mode == 'Y'){
    for(int i = 0; i < songs.size(); i++){
      if(songs.at(i).getyear() == year){
        temp.push_back(songs.at(i));
      }
    }
  }
  else if (mode == 'D'){
    for(int i = 0; i < songs.size(); i++){
      if((songs.at(i).getyear()/10) == (year/10)){
        temp.push_back(songs.at(i));
      }
    }
  }
  else{
    return;
  }

  if(temp.size() <= 0){
    cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
    return;
  }

  vector<Song> tempz, temped;
  for(int i = 0; i < temp.size(); i++){
    if(temp.at(i).getrank() == 1){
      temped.push_back(temp.at(i));
    }
  }
  for(int i = 0; i < temped.size(); i++){
    temphighest = 0;
    for(int j = i+1; j < temped.size(); j++){
      if((temped.at(i).gettitle() == temped.at(j).gettitle()) && (temped.at(i).getartist() == temped.at(j).getartist())){
        temphighest++;
      }
    }
    if(temphighest > highest){
      tempz.clear();
      highest = temphighest;
      tempz.push_back(temped.at(i));
    }
    else if(temphighest == highest){
      tempz.push_back(temped.at(i));
    }
  }
  cout << "The song(s) with the most #1 occurrences for selected time period is: "<< endl;
  for(int i = 0; i < tempz.size(); i++){
  
    cout << "        Song Title: " << tempz.at(i).gettitle() << "\n        Artist: " << tempz.at(i).getartist() << "\n        # of occurrences: " << highest+1 << endl;
    }
}

//longestsong
void notdying(vector<Song> &songs, char mode, int year){
  int index, temphigh, highest;
  vector<Song> temp;
  mode = toupper(mode);
  if(cin.fail()){
    cin.clear();
    cin.ignore(1000, '\n');
    return;
  }
  else if(mode == 'Y'){
    for(int i = 0; i < songs.size(); i++){
      if(songs.at(i).getyear() == year){
        temp.push_back(songs.at(i));
      }
    }
  }
  else if (mode == 'D'){
    for(int i = 0; i < songs.size(); i++){
      if((songs.at(i).getyear()/10) == (year/10)){
        temp.push_back(songs.at(i));
      }
    }
  }
  else{
    return;
  }
  if(temp.size() < 1){
    cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
    return;
  }
  temphigh = 0;
  highest = 0;
  for(int i = 0; i < temp.size(); i++){
    temphigh = temp.at(i).getweeksonboard();
    if(temphigh < 1){
      continue;
    }
    if(temphigh > highest){
      highest = temphigh;
      index = i;
    }
    }
  cout << "The song with the highest number of weeks on the charts is:\n        " << temp.at(index).gettitle() << " by " << temp.at(index).getartist() << " with " << temp.at(index).getweeksonboard() << " weeks on the chart." << endl;
  }
  


//trendiest song
void trendy(vector<Song> &songs, char mode, int year){
  int index = -1;
  int temphighest = 0;
  int highest = 0;
  vector<Song> temp;
  vector<Song> list;
  mode = toupper(mode);
  if(cin.fail()){
    cin.clear();
    cin.ignore(1000, '\n');
    return;
  }
  if(mode == 'Y'){
    for(int i = 0; i < songs.size(); i++){
      if(songs.at(i).getyear() == year){
        temp.push_back(songs.at(i));
      }
    }
  }
  else if (mode == 'D'){
    for(int i = 0; i < songs.size(); i++){
      if((songs.at(i).getyear()/10) == (year/10)){
        temp.push_back(songs.at(i));
      }
    }
  }
  else{
    return;
  }
  
  if(temp.size() < 1){
    cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
    return;
  }
  
  for(int i = 0; i < temp.size(); i++){
    temphighest = 0;
    if(temp.at(i).getlastrank() < 1){
      continue;
    }
    else if(temp.at(i).getartist() == "2"){
      continue;
    }
    else{
      temphighest = temp.at(i).getlastrank() - temp.at(i).getrank();
    }
    if(temphighest > highest){
      list.clear();
      highest = temphighest;
      list.push_back(temp.at(i));
    }
    else if(temphighest == highest){
      list.push_back(temp.at(i));
    }
  }
  cout << "The song(s) with the greatest climb from previous week to current week position:" << endl;
  for(int i = 0; i < list.size(); i++){
        cout << "        Song Title: " << list.at(i).gettitle() << "\n        Artist: " << list.at(i).getartist() << "\n        Week of: " << list.at(i).getmonth() << "/" << list.at(i).getday() << "/" << list.at(i).getyear() << "\n        Previous Week Position: " << list.at(i).getlastrank() << "\n        Current Week Position: " << list.at(i).getrank() << "\n        Difference of " << highest << " between previous week and current week position" << endl;
    }
}

//artist search
void lookup(vector<Song> &songs, string name){
  vector<Song> list;
  string author;
  for(int i = 0; i < name.length(); i++){
    name[i] = tolower(name[i]);
  }
  for(int i = 0; i < songs.size(); i++){
    if(songs.at(i).getrank() != 1 || songs.at(i).getpeakrank() != 1){
      continue;
    }
    author = songs.at(i).getartist();
    for(int j = 0; j < author.size(); j++){
      author[j] = tolower(author[j]);
    }
    if(author.find(name) != string::npos){
      list.push_back(songs.at(i));
    }
  }
  if(list.size() == 0) {
        cout << "No matching artists were found." << endl;
        return;
    }
  cout << "Retrieval of first 10 #1 records found based upon search by artist name:" << endl;
  for(int i = 0; i < 10; i++){
    if(i >= list.size()){
      break;
    }
    cout << i+1 << ") Song: " << list.at(i).gettitle() << "\n    Artist: " << list.at(i).getartist() << "\n    Week of: " << list.at(i).getmonth() << "/" << list.at(i).getday() << "/" << list.at(i).getyear() << "\n    Week Position: " << list.at(i).getrank() << endl;
  }
}


int main() {
  bool stateofmain, stateofmenu;
  int menuop1, menuop2, yeard;
  char menuop3;
  vector<Song> data;
  string stalker;

  cout << "Program 4: BillBoard Analysis \nCS 141, Spring 2022, UIC \n \nThis program will analyze weekly Billboard data spanning from 1960 - 2020.\n" << endl;
  stateofmain = true;
  stateofmenu = true;

  cout << "Select file option:\n   1. To analyze charts top 50: 1960 - 1980 data file\n   2. To analyze charts top 50: 1981 - 2000 data file\n   3. To analyze charts top 50: 2001 - 2020 data file\nYour choice --> ";
  cin >> menuop1;
  cout << endl;
  
  switch(menuop1){
    case 1:
      charts(data, menuop1);
      break;
  
    case 2:
    charts(data, menuop1);
    break;
  
    case 3:
    charts(data, menuop1);
    break;
  
    default:
    cout << "Invalid value. Exiting Program.";
    return 0;
  };
  
  while(stateofmain){
    

    cout << "\nSelect a menu option: \n   1. Display overall information about the data\n   2. Display the Billboard info of the song with the most #1 occurrences for a given decade or year\n   3. Display the Billboard info for the most long-lasting song on the charts for a given decade or year\n   4. Display the Billboard info for the song with the greatest weekly climb on the charts given a decade or year\n   5. Artist Search - Return the Billboard info for records that matches user input for artist search\n   6. Exit\nYour choice --> ";
    cin >> menuop2;
        
        //menuop2 = stoi(menuop2);
        switch(menuop2){
          //overall info
          case 1:
            cout << endl;
            numberofsongs(data, menuop1);
            break;

          //#1 song
          case 2:
            do{
              cout << endl;
              cout << "Enter D to select a decade or Y to select a year.\nYour choice --> ";
              cin >> menuop3;
              cout << endl;
              menuop3 = toupper(menuop3);
              if(menuop3 == 'D'){
                cout << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010)." << endl;
                cin >> yeard;
                popsong(data, menuop3, yeard);
                stateofmenu = false;
              }
              else if(menuop3 == 'Y'){
                cout << "Enter the year you would like to choose (e.g. 2001)." << endl;
                cin >> yeard;
                popsong(data, menuop3, yeard);
                stateofmenu = false;
              }
              else{
                cout << "Invalid entry. Try again." << endl;
                stateofmenu = true;
              }
            }
            while(stateofmenu);
            break;

          //never dying song
          case 3:
            cout << endl;
            do{
              cout << "Enter D to select a decade or Y to select a year.\nYour choice --> ";
              cin >> menuop3;
              cout << endl;
              menuop3 = toupper(menuop3);
              if(menuop3 == 'D'|| menuop3 == 'd'){
                cout << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010)." << endl;
                cin >> yeard;
                notdying(data, menuop3, yeard);
                stateofmenu = false;
              }
              else if(menuop3 == 'Y' || menuop3 == 'Y'){
                cout << "Enter the year you would like to choose (e.g. 2001)." << endl;
                cin >> yeard;
                notdying(data, menuop3, yeard);
                stateofmenu = false;
              }
              else if(menuop3 == 'N' || menuop3 == 'n'){
                cout << "Invalid entry. Try again." << endl;
                stateofmenu = true;
              }
              else{
                cout << "Invalid entry. Try again." << endl;
                stateofmenu = true;
              }
            }
            while(stateofmenu);
            break;

          //trendiest song
          case 4:
            cout << endl;
            do{
              cout << "Enter D to select a decade or Y to select a year.\nYour choice --> ";
              cin >> menuop3;
              cout << endl;
              menuop3 = toupper(menuop3);
              if(menuop3 == 'D'){
                cout << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010)." << endl;
                cin >> yeard;
                trendy(data, menuop3, yeard);
                stateofmenu = false;
              }
              else if(menuop3 == 'Y'){
                cout << "Enter the year you would like to choose (e.g. 2001)." << endl;
                cin >> yeard;
                trendy(data, menuop3, yeard);
                stateofmenu = false;
              }
              else{
                cout << "Invalid entry. Try again." << endl;
                stateofmenu = true;
              }
            }
            while(stateofmenu);
            break;

          //lookup
          case 5:
            cout << endl;
            cout << "Enter search text to retrieve first 10 records of #1 songs that match by artist name:" << endl;
            cin.ignore();
            getline(cin, stalker);
            lookup(data, stalker);
            break;

          //exit
          case 6:
            stateofmain = false;
            stateofmenu = false;
            break;
          
          default:
            if(cin.fail()){
              cin.clear();
              cin.ignore(1000, '\n');
            }
            
            cout << "\nInvalid value.  Please re-enter a value from the menu options below." << endl;
            cin.clear();
            break;
        }
  }

   return 0;
}
