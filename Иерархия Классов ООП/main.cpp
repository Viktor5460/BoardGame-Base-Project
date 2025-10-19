#include "BoardGame.h"
#include "Player.h"
#include "Match.h"
#include "RatingFilter.h"
#include "FeatureFilter.h"
#include "SimilarGamesFilter.h"
#include "GameDatabase.h"
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::cout << "=====================================================" << std::endl;
    std::cout << "===   ТЕСТИРОВАНИЕ ИЕРАРХИИ КЛАССОВ BOARDGAME    ===" << std::endl;
    std::cout << "=====================================================" << std::endl;
    
    // запуск тестов всех классов
    Player::runTests();
    Match::runTests();
    RatingFilter::runTests();
    FeatureFilter::runTests();
    SimilarGamesFilter::runTests();
    GameDatabase::runTests();
    
    std::cout << "\n=====================================================" << std::endl;
    std::cout << "===       ВСЕ ТЕСТЫ УСПЕШНО ЗАВЕРШЕНЫ            ===" << std::endl;
    std::cout << "=====================================================" << std::endl;
    
    std::cout << "\n=== ДЕМОНСТРАЦИЯ РАБОТЫ СИСТЕМЫ ===" << std::endl;
    
    // создаем базу данных и наполняем её
    GameDatabase db;
    
    // добавляем игры с признаками
    BoardGame* chess = new BoardGame("Шахматы", "Классическая стратегия", 2, 2, "Стандарт");
    chess->addFeature("Жанр", "Абстрактная стратегия");
    chess->addFeature("Сложность", "Высокая");
    
    BoardGame* carcassonne = new BoardGame("Каркассон", "Строительство тайлами", 2, 6, "Big Box");
    carcassonne->addFeature("Жанр", "Семейная");
    carcassonne->addFeature("Сложность", "Средняя");
    
    BoardGame* catan = new BoardGame("Колонизаторы", "Торговля ресурсами", 3, 4, "5-е издание");
    catan->addFeature("Жанр", "Стратегия");
    catan->addFeature("Сложность", "Средняя");
    
    db.addGame(chess);
    db.addGame(carcassonne);
    db.addGame(catan);
    
    // добавляем игроков
    db.addPlayer(new Player("ivan", "Иван"));
    db.addPlayer(new Player("maria", "Мария"));
    db.addPlayer(new Player("petr", "Петр"));
    
    // выставляем оценки
    db.addRating("Шахматы", "ivan", 5);
    db.addRating("Шахматы", "maria", 5);
    db.addRating("Каркассон", "ivan", 4);
    db.addRating("Каркассон", "petr", 5);
    db.addRating("Колонизаторы", "maria", 4);
    db.addRating("Колонизаторы", "petr", 4);
    
    // добавляем партии
    Match* m1 = new Match("m1", "Шахматы", "2024-10-01");
    m1->addPlayerResult("ivan", 1.0);
    m1->addPlayerResult("maria", 0.0);
    db.addMatch(m1);
    
    Match* m2 = new Match("m2", "Каркассон", "2024-10-05");
    m2->addPlayerResult("ivan", 95.0);
    m2->addPlayerResult("maria", 88.0);
    m2->addPlayerResult("petr", 102.0);
    db.addMatch(m2);
    
    // добавляем схожесть игр
    db.addSimilarity("Шахматы", "Колонизаторы");
    
    db.printStatistics();
    
    // демонстрация фильтров
    std::cout << "\n--- Поиск игр с рейтингом >= 4.5 ---" << std::endl;
    RatingFilter highRating(4.5);
    std::vector<BoardGame*> highRatedGames = db.findGames(&highRating);
    for (BoardGame* game : highRatedGames) {
        std::cout << game->getName() << " (рейтинг: " << game->getAverageRating() << ")" << std::endl;
    }
    
    std::cout << "\n--- Поиск стратегических игр ---" << std::endl;
    std::map<std::string, std::string> strategyFeature;
    strategyFeature["Жанр"] = "Стратегия";
    FeatureFilter strategyFilter(strategyFeature);
    std::vector<BoardGame*> strategyGames = db.findGames(&strategyFilter);
    for (BoardGame* game : strategyGames) {
        std::cout << game->getName() << std::endl;
    }
    
    std::cout << "\n--- Игры, похожие на Шахматы ---" << std::endl;
    std::vector<std::string> refs = {"Шахматы"};
    SimilarGamesFilter similarFilter(refs, db.getSimilarityData());
    std::vector<BoardGame*> similarGames = db.findGames(&similarFilter);
    for (BoardGame* game : similarGames) {
        std::cout << game->getName() << std::endl;
    }
    
    std::cout << "\n--- Рейтинг игрока Ivan в Каркассон ---" << std::endl;
    double rating = db.getPlayerRatingInGame("ivan", "Каркассон");
    std::cout << "Рейтинг: " << rating << std::endl;
    
    // демонстрация операторов
    std::cout << "\n--- operator bool() для проверки валидности ---" << std::endl;
    BoardGame* validGame = db["Шахматы"];
    BoardGame* invalidGame = db["НесуществующаяИгра"];
    
    if (validGame && *validGame) {
        std::cout << "✓ Игра 'Шахматы' валидна и существует" << std::endl;
    }
    if (!invalidGame) {
        std::cout << "✓ Игра 'НесуществующаяИгра' не найдена (operator[] вернул nullptr)" << std::endl;
    }
    
    std::cout << "\n--- operator[] для доступа к играм ---" << std::endl;
    BoardGame* game = db["Каркассон"];
    if (game) {
        std::cout << "Доступ через operator[]: " << game->getName() 
                  << " (рейтинг: " << game->getAverageRating() << ")" << std::endl;
    }
    
    std::cout << "\n--- Статический метод getTotalGamesCreated() ---" << std::endl;
    std::cout << "Всего игр создано за время работы программы: " 
              << BoardGame::getTotalGamesCreated() << std::endl;
    
    std::cout << "\n--- Перегрузка операторов сравнения ---" << std::endl;
    BoardGame* chess2 = db["Шахматы"];
    BoardGame* catan2 = db["Колонизаторы"];
    if (chess2 && catan2) {
        if (*chess2 > *catan2) {
            std::cout << "Шахматы (рейтинг " << chess2->getAverageRating() 
                      << ") имеют более высокий рейтинг, чем Колонизаторы (рейтинг " 
                      << catan2->getAverageRating() << ")" << std::endl;
        }
    }
    
    std::cout << "\n=== ДЕМОНСТРАЦИЯ ЗАВЕРШЕНА ===" << std::endl;
    
    return 0;
}
