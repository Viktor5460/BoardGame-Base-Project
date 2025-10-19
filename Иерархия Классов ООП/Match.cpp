#include "Match.h"
#include <algorithm>
#include <limits>
#include <iomanip>

Match::Match() : matchId(""), gameName(""), date("") {}

Match::Match(const std::string& matchId, const std::string& gameName, const std::string& date)
    : matchId(matchId), gameName(gameName), date(date) {}

Match::~Match() {}
std::string Match::getMatchId() const {
    return matchId;
}

std::string Match::getGameName() const {
    return gameName;
}

std::string Match::getDate() const {
    return date;
}

const std::map<std::string, double>& Match::getPlayerResults() const {
    return playerResults;
}

int Match::getPlayerCount() const {
    return playerResults.size();
}

bool Match::addPlayerResult(const std::string& playerId, double result) {
    // игрок может участвовать в партии только один раз
    if (playerResults.find(playerId) != playerResults.end()) {
        return false;
    }
    
    playerResults[playerId] = result;
    return true;
}

double Match::getPlayerResult(const std::string& playerId) const {
    auto it = playerResults.find(playerId);
    if (it != playerResults.end()) {
        return it->second;
    }
    return -1.0;
}

bool Match::hasPlayer(const std::string& playerId) const {
    return playerResults.find(playerId) != playerResults.end();
}

std::string Match::getWinner() const {
    if (playerResults.empty()) {
        return "";
    }
    
    // находим игрока с максимальным результатом
    auto maxElement = std::max_element(
        playerResults.begin(), 
        playerResults.end(),
        [](const std::pair<std::string, double>& a, const std::pair<std::string, double>& b) {
            return a.second < b.second;
        }
    );
    
    return maxElement->first;
}

bool Match::operator<(const Match& other) const {
    return this->date < other.date;
}

std::ostream& operator<<(std::ostream& os, const Match& match) {
    os << "Match[ID: " << match.matchId 
       << ", Game: " << match.gameName 
       << ", Date: " << match.date 
       << ", Players: " << match.playerResults.size() << "]";
    return os;
}
void Match::printInfo() const {
    std::cout << "=== Партия ===" << std::endl;
    std::cout << "ID: " << matchId << std::endl;
    std::cout << "Игра: " << gameName << std::endl;
    std::cout << "Дата: " << date << std::endl;
    std::cout << "Количество игроков: " << playerResults.size() << std::endl;
    
    if (!playerResults.empty()) {
        std::cout << "Результаты:" << std::endl;
        for (const auto& pair : playerResults) {
            std::cout << "  " << pair.first << ": " << std::fixed 
                      << std::setprecision(1) << pair.second;
            if (pair.first == getWinner()) {
                std::cout << " (победитель)";
            }
            std::cout << std::endl;
        }
    }
}

void Match::runTests() {
    std::cout << "\n=== Тестирование класса Match ===" << std::endl;
    
    Match m1("match_001", "Шахматы", "2024-01-15");
    
    std::cout << "Тест 1 - Создание партии: ";
    if (m1.getMatchId() == "match_001" && 
        m1.getGameName() == "Шахматы" && 
        m1.getDate() == "2024-01-15") {
        std::cout << "PASSED" << std::endl;
    } else {
        std::cout << "FAILED" << std::endl;
    }
    
    m1.addPlayerResult("player_001", 85.5);
    m1.addPlayerResult("player_002", 92.0);
    m1.addPlayerResult("player_003", 78.3);
    
    std::cout << "Тест 2 - Добавление результатов: ";
    if (m1.getPlayerCount() == 3) {
        std::cout << "PASSED" << std::endl;
    } else {
        std::cout << "FAILED" << std::endl;
    }
    
    bool duplicate = m1.addPlayerResult("player_001", 100.0);
    
    std::cout << "Тест 3 - Защита от дублирования: ";
    if (!duplicate && m1.getPlayerCount() == 3) {
        std::cout << "PASSED" << std::endl;
    } else {
        std::cout << "FAILED" << std::endl;
    }
    
    double result = m1.getPlayerResult("player_002");
    
    std::cout << "Тест 4 - Получение результата: ";
    if (result == 92.0) {
        std::cout << "PASSED" << std::endl;
    } else {
        std::cout << "FAILED" << std::endl;
    }
    
    std::string winner = m1.getWinner();
    
    std::cout << "Тест 5 - Определение победителя: ";
    if (winner == "player_002") {
        std::cout << "PASSED (победитель: " << winner << ")" << std::endl;
    } else {
        std::cout << "FAILED" << std::endl;
    }
    
    std::cout << "Тест 6 - Проверка участия: ";
    if (m1.hasPlayer("player_001") && !m1.hasPlayer("player_999")) {
        std::cout << "PASSED" << std::endl;
    } else {
        std::cout << "FAILED" << std::endl;
    }
    
    Match m2("match_002", "Каркассон", "2024-02-20");
    
    std::cout << "Тест 7 - Сравнение по дате: ";
    if (m1 < m2) {
        std::cout << "PASSED" << std::endl;
    } else {
        std::cout << "FAILED" << std::endl;
    }
    
    std::cout << "Тест 8 - Оператор вывода: " << m1 << std::endl;
    
    std::cout << "=== Тестирование Match завершено ===\n" << std::endl;
}

