#include "BoardGame.h"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cmath>

int BoardGame::totalGamesCreated = 0;

BoardGame::BoardGame() 
    : name(""), description(""), minPlayers(1), maxPlayers(1), edition("") {
    ++totalGamesCreated;
}

BoardGame::BoardGame(const std::string& name, const std::string& description, 
                     int minPlayers, int maxPlayers, const std::string& edition)
    : name(name), description(description), minPlayers(minPlayers), 
      maxPlayers(maxPlayers), edition(edition) {
    ++totalGamesCreated;
}

BoardGame::~BoardGame() {
}

std::string BoardGame::getName() const {
    return name;
}

std::string BoardGame::getDescription() const {
    return description;
}

int BoardGame::getMinPlayers() const {
    return minPlayers;
}

int BoardGame::getMaxPlayers() const {
    return maxPlayers;
}

std::string BoardGame::getEdition() const {
    return edition;
}

const std::map<std::string, int>& BoardGame::getRatings() const {
    return ratings;
}

const std::map<std::string, std::string>& BoardGame::getFeatures() const {
    return features;
}
void BoardGame::setName(const std::string& name) {
    this->name = name;
}

void BoardGame::setDescription(const std::string& description) {
    this->description = description;
}

void BoardGame::setMinPlayers(int minPlayers) {
    this->minPlayers = minPlayers;
}

void BoardGame::setMaxPlayers(int maxPlayers) {
    this->maxPlayers = maxPlayers;
}

void BoardGame::setEdition(const std::string& edition) {
    this->edition = edition;
}

bool BoardGame::addRating(const std::string& playerId, int rating) {
    // проверяем корректность оценки
    if (rating < 1 || rating > 5) {
        return false;
    }
    
    // игрок может оценить игру только один раз
    if (ratings.find(playerId) != ratings.end()) {
        return false;
    }
    
    ratings[playerId] = rating;
    return true;
}

bool BoardGame::updateRating(const std::string& playerId, int rating) {
    if (rating < 1 || rating > 5) {
        return false;
    }
    
    if (ratings.find(playerId) == ratings.end()) {
        return false;
    }
    
    ratings[playerId] = rating;
    return true;
}

bool BoardGame::removeRating(const std::string& playerId) {
    auto it = ratings.find(playerId);
    if (it != ratings.end()) {
        ratings.erase(it);
        return true;
    }
    return false;
}

double BoardGame::getAverageRating() const {
    if (ratings.empty()) {
        return 0.0;
    }
    
    // вычисляем среднее арифметическое всех оценок
    int sum = 0;
    for (const auto& pair : ratings) {
        sum += pair.second;
    }
    
    return static_cast<double>(sum) / ratings.size();
}

bool BoardGame::addFeature(const std::string& featureName, const std::string& featureValue) {
    if (features.find(featureName) != features.end()) {
        return false; 
    }
    
    features[featureName] = featureValue;
    return true;  
}

bool BoardGame::updateFeature(const std::string& featureName, const std::string& featureValue) {
    if (features.find(featureName) == features.end()) {
        return false;
    }
    
    features[featureName] = featureValue;
    return true;  
}

bool BoardGame::removeFeature(const std::string& featureName) {
    auto it = features.find(featureName);
    if (it != features.end()) {
        features.erase(it);
        return true;
    }
    return false;
}

std::string BoardGame::getFeature(const std::string& featureName) const {
    auto it = features.find(featureName);
    if (it != features.end()) {
        return it->second;
    }
    return "";
}

bool BoardGame::hasFeature(const std::string& featureName) const {
    return features.find(featureName) != features.end();
}

bool BoardGame::operator<(const BoardGame& other) const {
    return this->getAverageRating() < other.getAverageRating();
}

bool BoardGame::operator==(const BoardGame& other) const {
    return std::abs(this->getAverageRating() - other.getAverageRating()) < 0.001;
}

bool BoardGame::operator<=(const BoardGame& other) const {
    return *this < other || *this == other;
}

bool BoardGame::operator>(const BoardGame& other) const {
    return !(*this <= other);
}

bool BoardGame::operator>=(const BoardGame& other) const {
    return *this > other || *this == other;
}

BoardGame::operator bool() const {
    // игра валидна, если у неё есть название
    return !name.empty();
}

size_t BoardGame::getRatingsCount() const {
    return ratings.size();
}

int BoardGame::getTotalGamesCreated() {
    return totalGamesCreated;
}
void BoardGame::printInfo() const {
    std::cout << "=== " << name << " ===" << std::endl;
    std::cout << "Описание: " << description << std::endl;
    std::cout << "Игроки: " << minPlayers << "-" << maxPlayers << std::endl;
    std::cout << "Издание: " << edition << std::endl;
    std::cout << "Средняя оценка: " << std::fixed << std::setprecision(2) 
              << getAverageRating() << std::endl;
    std::cout << "Количество оценок: " << ratings.size() << std::endl;
}

void BoardGame::printRatings() const {
    std::cout << "Оценки для игры \"" << name << "\":" << std::endl;
    if (ratings.empty()) {
        std::cout << "  Оценок пока нет." << std::endl;
    } else {
        for (const auto& pair : ratings) {
            std::cout << "  " << pair.first << ": " << pair.second << std::endl;
        }
    }
}

void BoardGame::printFeatures() const {
    std::cout << "Признаки игры \"" << name << "\":" << std::endl;
    if (features.empty()) {
        std::cout << "  Признаков пока нет." << std::endl;
    } else {
        for (const auto& pair : features) {
            std::cout << "  " << pair.first << ": " << pair.second << std::endl;
        }
    }
}
