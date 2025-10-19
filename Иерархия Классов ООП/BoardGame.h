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
    std::map<std::string, int> ratings; // игрок -> оценка (1-5)
    int minPlayers;                      
    int maxPlayers;                     
    std::string edition;                 
    std::map<std::string, std::string> features; // дополнительные характеристики
    
    static int totalGamesCreated; // счетчик созданных игр 

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
    
    const std::map<std::string, int>& getRatings() const;
    const std::map<std::string, std::string>& getFeatures() const;
    
    // сеттеры
    void setName(const std::string& name);
    void setDescription(const std::string& description);
    void setMinPlayers(int minPlayers);
    void setMaxPlayers(int maxPlayers);
    void setEdition(const std::string& edition);
    
    // работа с оценками
    bool addRating(const std::string& playerId, int rating);
    bool updateRating(const std::string& playerId, int rating);
    bool removeRating(const std::string& playerId);
    double getAverageRating() const;
    
    // работа с признаками
    bool addFeature(const std::string& featureName, const std::string& featureValue);
    bool updateFeature(const std::string& featureName, const std::string& featureValue);
    bool removeFeature(const std::string& featureName);
    std::string getFeature(const std::string& featureName) const;
    bool hasFeature(const std::string& featureName) const;
    
 
    // операторы сравнения (по среднему рейтингу)
    bool operator<(const BoardGame& other) const;
    bool operator==(const BoardGame& other) const;
    bool operator<=(const BoardGame& other) const;
    bool operator>(const BoardGame& other) const;
    bool operator>=(const BoardGame& other) const;
    
    explicit operator bool() const; // проверка валидности
    size_t getRatingsCount() const;
    static int getTotalGamesCreated();

    // вывод информации
    void printInfo() const;
    void printRatings() const;
    void printFeatures() const;
};

#endif
