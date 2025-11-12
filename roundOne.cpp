/***************************************
Round One
Author: Mitchell Bell
Date Completed: 11/12/25
Description: This program will tally votes for a candidates and process the results
using plurality voting
***************************************/

#include <iostream>
#include "HashTable.hpp"
#include "LinkedList.hpp"
using namespace std;

// Implement definition of Candidate data type here
class Candidate
{
    private:
    string id_;
    string name_;

    public:
    Candidate(string id, string name)
        : id_(id), name_(name){}

    string getId()
    {
        return id_;
    }
    string getName()
    {
        return name_;
    }
};

// Implement definition of Ballot data type here
class Ballot
{
    private:
    string firstChoice_;
    string secondChoice_;
    string thirdChoice_;

    public:
    Ballot(string first, string second, string third)
        : firstChoice_(first), secondChoice_(second), thirdChoice_(third){}

    string getHighestCandidate()
    {
        return firstChoice_;
    }
};



// Implement body of "tallyRound1Votes" non-member function
HashTable<int> tallyRound1Votes(LinkedList<Ballot> &ballots, HashTable<Candidate> &candidates)
{
    HashTable<int> voteTable;
    typename LinkedList<Ballot>::Iterator iter = ballots.generateIterator();
    while (iter.hasNext())
    {
        Ballot *currentBallotPtr = iter.current();
        Ballot currentBallot = *currentBallotPtr;
        string topId = currentBallot.getHighestCandidate();
        int *votePtr = voteTable.get(topId);
        if (votePtr != nullptr)
        {
            int currentVotes = *votePtr;
            voteTable.remove(topId);
            voteTable.add(topId, currentVotes + 1);
        }
        else
        {
            voteTable.add(topId, 1);
        }
        iter.next();
    }
    return voteTable;
}

// Implement body of "processRound1Results" non-member function
void processRound1Results(HashTable<int> &talliedVotes, HashTable<Candidate> &candidates, float halfOfVotes)
{
    cout<<"Round 1 Results: "<<endl;
    string winnerId;
    string loserId;
    int highestVotes = 0;
    int lowestVotes = 999;

    typename HashTable<Candidate>::Iterator iter = candidates.generateIterator();
    while (iter.hasNext())
    {
        pair<string, Candidate> *entry = iter.current();
        string candidateId = entry->first;
        Candidate c = entry->second;

        int votes = 0;
        int *votePtr = talliedVotes.get(candidateId);
        if (votePtr != nullprt)
        {
            votes = *votePtr;
        }
        cout<<c.getName()<<": "<<votes<<" vote(s)"<<endl;

        if (votes > highestVotes)
        {
            highestVotes = votes;
            winnerId = candidateId;
        }
        if (votes < lowestVotes)
        {
            lowestVotes = votes;
            loserId = candidateId;
        }
        iter.next();
    }
    cout<<endl;
    if(float(highestVotes) > halfOfVotes)
    {
        Candidate *winner = candidates.get(winnerId);
        cout<<winner->getName()<<" is the winner!"<<endl;
    }
    else
    {
        cout<<"No candidate had more than 50% of the votes"<<endl;
        Candidate *loser = candidate.get(loserId);
        cout<<loser->getName()<<" had the least number of votes and will be eliminated"<<endl;
    }
    
}


// This function is used to test implementation of the "tallyRound1Votes"
// and "processRound1Results" non-member functions.
void test1()
{
    LinkedList<Ballot> ballots;
    ballots.pushFront(Ballot("CC", "CB", "CA"));
    ballots.pushFront(Ballot("CB", "CA", "CC"));
    ballots.pushFront(Ballot("CC", "CB", "CA"));
    ballots.pushFront(Ballot("CC", "CA", "CB"));
    ballots.pushFront(Ballot("CA", "CB", "CC"));
    ballots.pushFront(Ballot("CC", "CA", "CB"));
    ballots.pushFront(Ballot("CB", "CA", "CC"));
    ballots.pushFront(Ballot("CA", "CB", "CC"));
    ballots.pushFront(Ballot("CB", "CC", "CA"));
    ballots.pushFront(Ballot("CA", "CB", "CC"));
    ballots.pushFront(Ballot("CC", "CB", "CA"));
    ballots.pushFront(Ballot("CC", "CA", "CB"));
    ballots.pushFront(Ballot("CB", "CA", "CC"));

  
    HashTable<Candidate> candidates;
    candidates.add("CA", Candidate("CA", "Candidate A"));
    candidates.add("CB", Candidate("CB", "Candidate B"));
    candidates.add("CC", Candidate("CC", "Candidate C"));



    int totalVotes(ballots.size());
    float halfOfVotes = float(totalVotes)/2;
    
    cout<<"Total Votes: "<<totalVotes<<endl<<endl;

    HashTable<int> talliedVotes = tallyRound1Votes(ballots, candidates);
    processRound1Results(talliedVotes, candidates, halfOfVotes);
}


// This function is used to test implementation of the "tallyRound1Votes"
// and "processRound1Results" non-member functions.
void test2()
{
    LinkedList<Ballot> ballots;
    ballots.pushFront(Ballot("3", "4", "2"));
    ballots.pushFront(Ballot("2", "1", "4"));
    ballots.pushFront(Ballot("4", "2", "3"));
    ballots.pushFront(Ballot("3", "1", "2"));
    ballots.pushFront(Ballot("1", "4", "2"));
    ballots.pushFront(Ballot("3", "1", "2"));
    ballots.pushFront(Ballot("3", "2", "1"));
    ballots.pushFront(Ballot("1", "2", "3"));
    ballots.pushFront(Ballot("3", "1", "4"));
    ballots.pushFront(Ballot("4", "2", "3"));
    ballots.pushFront(Ballot("3", "1", "2"));

  
    HashTable<Candidate> candidates;
    candidates.add("1", Candidate("1", "Candidate A"));
    candidates.add("2", Candidate("2", "Candidate B"));
    candidates.add("3", Candidate("3", "Candidate C"));
    candidates.add("4", Candidate("4", "Candidate D"));


    int totalVotes(ballots.size());
    float halfOfVotes = float(totalVotes)/2;
    
    cout<<"Total Votes: "<<totalVotes<<endl<<endl;

    HashTable<int> talliedVotes = tallyRound1Votes(ballots, candidates);
    processRound1Results(talliedVotes, candidates, halfOfVotes);
}



// Driver code calls both tests
int main()
{
    cout<<"Test 1:\n\n";
    test1();

    cout<<"\n\nTest 2:\n\n";
    test2();

    return 0;
}