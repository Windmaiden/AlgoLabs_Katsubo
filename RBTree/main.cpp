#include <iostream>
#include <vector>
#include "ITree.h"

using namespace std;


//--------------------------------------------//


//brief The FootballPlayer struct
//Football player object class

struct FootballPlayer
{
   
   //brief mName - Name team
 
   std::string mName;

   
  //brief mCofficient - number of goals scored divided
  //by number of games played in a tournament
   
   double      mCofficient;

   //-----------------------------------------------------//

   
   //brief FootballPlayer - Constructor
   //param _name - name team
   //param _cofficient - number of games won divided by all games played
   
   FootballPlayer(std::string _name , double _cofficient = 0)
   : mName(_name) ,  mCofficient(_cofficient)
   {

   }

};



 //brief The FuttballTeam struct
 //football team object class

struct FuttballTeam : public ClassData
{

     
    //brief mPlayersNames - team players
     
     std::vector<FootballPlayer> mPlayersNames;


     /// Constructor
     FuttballTeam(std::string _name , int _priority = 0)
     : ClassData(_name , _priority)
     {

     }


    
    // brief AddPlayer - add player to team
	//param name - name player
     
     void AddPlayer( FootballPlayer name )
     {
         mPlayersNames.push_back(name);
     }


     void RemovePlayer( FootballPlayer name )
     {
         for(auto it = mPlayersNames.begin(); it != mPlayersNames.end(); ++it)
         {
             if(it->mName == name.mName)
             {
                 mPlayersNames.erase(it);
             }
         }
     }


     
      //brief Print - Output print
     
     void Print() const
     {
         cout << " -NAMES-FUTTBALLISTS:(";
         for(auto it = mPlayersNames.begin(); it != mPlayersNames.end(); ++it)
         {
             cout<< it->mName << "-" << it->mCofficient << "%, ";
         }
         cout << ")";
     }
};



int main(int argc, char **argv)
{



    
   // create new teams for tree
    
    FuttballTeam *Team1 = new FuttballTeam("RealMadrid" ,2 );
    FuttballTeam *Team2 = new FuttballTeam("Milan" , 5);
    FuttballTeam *Team3 = new FuttballTeam("Chalsi" , 3);
    FuttballTeam *Team4 = new FuttballTeam("Inter" ,4);
    FuttballTeam *Team5 = new FuttballTeam("Barselona" ,1);
    FuttballTeam *Team6 = new FuttballTeam("Valencia" ,10);

    
    // Recruit players in the team
    
    Team1->AddPlayer(FootballPlayer("wera",55));
    Team1->AddPlayer(FootballPlayer("vasj",33));
    Team1->AddPlayer(FootballPlayer("grisha",56));

    Team2->AddPlayer(FootballPlayer("sveta",5));
    Team2->AddPlayer(FootballPlayer("lisa",20));
    Team2->AddPlayer(FootballPlayer("gnomic",30));

    Team3->AddPlayer(FootballPlayer("siera",60));
    Team3->AddPlayer(FootballPlayer("ibra",77));
    Team3->AddPlayer(FootballPlayer("libra",88));

    Team4->AddPlayer(FootballPlayer("sveta",88));
    Team4->AddPlayer(FootballPlayer("petro",67));
    Team4->AddPlayer(FootballPlayer("grindo",67));

    Team5->AddPlayer(FootballPlayer("gacji",4));
    Team5->AddPlayer(FootballPlayer("lol",44));
    Team5->AddPlayer(FootballPlayer("tikto",66));

    Team6->AddPlayer(FootballPlayer("ira",66));
    Team6->AddPlayer(FootballPlayer("katj",66));
    Team6->AddPlayer(FootballPlayer("olj",44));


    cout << "LISTS COMANDS" << endl;
    cout << Team1->mName << "  ";
    Team1->Print();
    cout<< endl;

    cout << Team2->mName << "  ";
    Team2->Print();
    cout<< endl;

    cout << Team3->mName << "  ";
    Team3->Print();
    cout<< endl;

    cout << Team4->mName << "  ";
    Team4->Print();
    cout<< endl;

    cout << Team5->mName << "  ";
    Team5->Print();
    cout<< endl;

    cout << Team6->mName << "  ";
    Team6->Print();
    cout<< endl;


    
   // brief TreeTour - Build a tree
   
    ITree TreeTour;
    TreeTour.Add(Team1);
    TreeTour.Add(Team2);
    TreeTour.Add(Team3);
    TreeTour.Add(Team4);
    TreeTour.Add(Team5);
    TreeTour.Add(Team6);

    std::cout << "\n\n TOUR-TABLE" << std::endl;
    TreeTour.Print();


   
    //Remove the Inter team from the tournament tree table,
   
    std::cout << "\n\n DELETE-TEAM( Inter ) :: " << std::endl;
    TreeTour.Remove(TreeTour.Find(Team4));
    TreeTour.Print();


    
   // Displaying the tree table with additional information
    
    std::cout << "\n\n TOUR-TABLE and NAMES-PLAYERS:: " << std::endl;
    TreeTour.Print(true);


    
    // The number of games of each team, except Inter
    
    cout << "\n\n number of games of each team in the championship:: " << std::endl;
    cout << Team1->mName << ": " << TreeTour.Find(Team1)->size << std::endl;
    cout << Team2->mName << ": " << TreeTour.Find(Team2)->size << std::endl;
    cout << Team3->mName << ": " << TreeTour.Find(Team3)->size << std::endl;
    cout << Team5->mName << ": " << TreeTour.Find(Team5)->size << std::endl;
    cout << Team6->mName << ": " << TreeTour.Find(Team6)->size << std::endl;


    /// Clear memory
    delete  Team1;
    delete  Team2;
    delete  Team3;
    delete  Team4;
    delete  Team5;
    delete  Team6;

}
