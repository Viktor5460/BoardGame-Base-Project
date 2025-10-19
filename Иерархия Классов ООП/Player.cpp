#include "Player.h"
#include <numeric>
#include <iomanip>

Player::Player() : playerId(""), name("") {}

Player::Player(const std::string& playerId, const std::string& name)
    : playerId(playerId), name(name) {}

Player::~Player() {}

std::string Player::getPlayerId() const {
    return playerId;
}

std::string Player::getName() const {
    return name;
}

const std::vector<std::string>& Player::getMatchHistory() const {
    return matchHistory;
}

void Player::setName(const std::string& name) {
    this->name = name;
}

void Player::addMatchToHistory(const std::string& matchId) {
    matchHistory.push_back(matchId);
}

double Player::calculateRatingInGame(const std::vector<double>& results) const {
    if (results.empty()) {
        return 0.0;
    }
    
    // вычисляем средний результат по всем партиям
    double sum = std::accumulate(results.begin(), results.end(), 0.0);
    return sum / results.size();
}

bool Player::operator==(const Player& other) const {
    return this->playerId == other.playerId;
}

std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << "Player[ID: " << player.playerId;
    if (!player.name.empty()) {
        os << ", Name: " << player.name;
    }
    os << ", Matches played: " << player.matchHistory.size() << "]";
    return os;
}

void Player::printInfo() const {
    std::cout << "=== Игрок ===" << std::endl;
    std::cout << "ID: " << playerId << std::endl;
    if (!name.empty()) {
        std::cout << "Имя: " << name << std::endl;
    }
    std::cout << "Сыграно партий: " << matchHistory.size() << std::endl;
}
void Player::runTests() {
    std::cout << "\n=== Тестирование класса Player ===" << std::endl;
    
    Player p1("player_001", "Иван");
    Player p2("player_002");
    
    std::cout << "Тест 1 - Создание игроков: ";
    if (p1.getPlayerId() == "player_001" && p1.getName() == "Иван" &&
        p2.getPlayerId() == "player_002" && p2.getName().empty()) {
        std::cout << "PASSED" << std::endl;
    } else {
        std::cout << "FAILED" << std::endl;
    }
    
    p1.addMatchToHistory("match_1");
    p1.addMatchToHistory("match_2");
    p1.addMatchToHistory("match_3");
    
    std::cout << "Тест 2 - Добавление партий: ";
    if (p1.getMatchHistory().size() == 3) {
        std::cout << "PASSED" << std::endl;
    } else {
        std::cout << "FAILED" << std::endl;
    }
    
    std::vector<double> results = {85.5, 90.0, 78.3, 92.1};
    double rating = p1.calculateRatingInGame(results);
    
    std::cout << "Тест 3 - Расчет рейтинга: ";
    if (rating > 86.4 && rating < 86.5) {
        std::cout << "PASSED (рейтинг: " << std::fixed << std::setprecision(2) 
                  << rating << ")" << std::endl;
    } else {
        std::cout << "FAILED (ожидалось ~86.48, получено: " << rating << ")" << std::endl;
    }
    
    Player p3("player_001", "Другое имя");
    
    std::cout << "Тест 4 - Оператор сравнения: ";
    if (p1 == p3 && !(p1 == p2)) {
        std::cout << "PASSED" << std::endl;
    } else {
        std::cout << "FAILED" << std::endl;
    }
    
    std::cout << "Тест 5 - Оператор вывода: ";
    std::cout << p1 << std::endl;
    
    std::cout << "=== Тестирование Player завершено ===\n" << std::endl;
}

