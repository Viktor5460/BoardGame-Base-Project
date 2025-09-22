#ifndef BOARDGAME_H
#define BOARDGAME_H

#include <string>
#include <map>
#include <vector>
#include <iostream>

class BoardGame {
private:
    std::string name;                   
    std::string description;           
    std::map<std::string, int> ratings; //  (игрок -> оценка 1-5)
    int minPlayers;                      
    int maxPlayers;                     
    std::string edition;                 
    std::map<std::string, std::string> features; 

public:

    BoardGame();
    BoardGame(const std::string& name, const std::string& description, 
              int minPlayers, int maxPlayers, const std::string& edition);
    

    ~BoardGame();
    

    std::string getName() const;
    std::string getDescription() const;
    int getMinPlayers() const;
    int getMaxPlayers() const;
    std::string getEdition() const;
    std::map<std::string, int> getRatings() const;
    std::map<std::string, std::string> getFeatures() const;
    

    void setName(const std::string& name);
    void setDescription(const std::string& description);
    void setMinPlayers(int minPlayers);
    void setMaxPlayers(int maxPlayers);
    void setEdition(const std::string& edition);
    

    bool addRating(const std::string& playerId, int rating);
    bool updateRating(const std::string& playerId, int rating);
    bool removeRating(const std::string& playerId);
    double getAverageRating() const;
    

    bool addFeature(const std::string& featureName, const std::string& featureValue);
    bool updateFeature(const std::string& featureName, const std::string& featureValue);
    bool removeFeature(const std::string& featureName);
    std::string getFeature(const std::string& featureName) const;
    bool hasFeature(const std::string& featureName) const;
    
 
    bool operator<(const BoardGame& other) const;
    bool operator==(const BoardGame& other) const;
    bool operator<=(const BoardGame& other) const;
    bool operator>(const BoardGame& other) const;
    bool operator>=(const BoardGame& other) const;
    
   
    

    void printInfo() const;
    void printRatings() const;
    void printFeatures() const;
};

#endif
