#include "BoardGame.h"
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::cout << "=== Тестирование класса BoardGame ===" << std::endl;
    

    BoardGame game1("Шахматы", "Классическая стратегическая игра", 2, 2, "");
    BoardGame game2("Битва за Рокуган", "Area control game", 2, 5, "FFG");
    BoardGame game3("Каркассон", "Семейная игра с тайлами", 2, 6, "Big Box");
    
    std::cout << "\n1. Создание игр:" << std::endl;
    game1.printInfo();
    game2.printInfo();
    game3.printInfo();
    std::cout << std::endl;
    

    std::cout << "2. Тестирование операций с оценками:" << std::endl;
    

    game1.addRating("player1", 5);
    game1.addRating("player2", 4);
    game1.addRating("player3", 5);
    
    game2.addRating("player1", 3);
    game2.addRating("player2", 4);
    game2.addRating("player4", 2);
    
    game3.addRating("player2", 5);
    game3.addRating("player3", 4);
    game3.addRating("player4", 5);
    game3.addRating("player5", 3);
    
    std::cout << "Оценки добавлены:" << std::endl;
    game1.printRatings();
    game2.printRatings();
    game3.printRatings();
    

    std::cout << "\nИзменение оценки player1 для " << game1.getName() << " с 5 на 4:" << std::endl;
    if (game1.updateRating("player1", 4)) {
        std::cout << "Оценка успешно изменена" << std::endl;
    } else {
        std::cout << "Не удалось изменить оценку" << std::endl;
    }
    game1.printRatings();
    

    std::cout << "\nУдаление оценки player4 для " << game2.getName() << ":" << std::endl;
    if (game2.removeRating("player4")) {
        std::cout << "Оценка успешно удалена" << std::endl;
    } else {
        std::cout << "Не удалось удалить оценку" << std::endl;
    }
    game2.printRatings();
    

    std::cout << "\n3. Тестирование операций с признаками:" << std::endl;
    
    game1.addFeature("Жанр", "Стратегия");
    game1.addFeature("Сложность", "Высокая");
    game1.addFeature("Время игры", "30 минут");
    
    game2.addFeature("Жанр", "Area control");
    game2.addFeature("Сложность", "Средняя");
    game2.addFeature("Время игры", "90 минут");
    
    game3.addFeature("Жанр", "Семейная игра");
    game3.addFeature("Сложность", "Низкая");
    game3.addFeature("Время игры", "40 минут");
    game3.addFeature("Тип", "Выставление рабочих");
    
    std::cout << "Признаки добавлены:" << std::endl;
    game1.printFeatures();
    game2.printFeatures();
    game3.printFeatures();
    

    std::cout << "\nИзменение сложности " << game3.getName() << " с 'Низкая' на 'Средняя':" << std::endl;
    game3.updateFeature("Сложность", "Средняя");
    game3.printFeatures();

    std::cout << "\nУдаление признака 'Тип' для " << game3.getName() << ":" << std::endl;
    if (game3.removeFeature("Тип")) {
        std::cout << "Признак успешно удален" << std::endl;
    } else {
        std::cout << "Не удалось удалить признак" << std::endl;
    }
    game3.printFeatures();

    std::cout << "\n4. Тестирование операторов сравнения:" << std::endl;
    
    std::cout << "Средние оценки игр:" << std::endl;
    std::cout << game1.getName() << ": " << game1.getAverageRating() << std::endl;
    std::cout << game2.getName() << ": " << game2.getAverageRating() << std::endl;
    std::cout << game3.getName() << ": " << game3.getAverageRating() << std::endl;
    
    std::cout << "\nСравнения:" << std::endl;
    std::cout << game1.getName() << " > " << game2.getName() << ": " << (game1 > game2 ? "Да" : "Нет") << std::endl;
    std::cout << game3.getName() << " == " << game3.getName() << ": " << (game3 == game3 ? "Да" : "Нет") << std::endl;
    std::cout << game2.getName() << " < " << game3.getName() << ": " << (game2 < game3 ? "Да" : "Нет") << std::endl;
 
    std::cout << "\n5. Сортировка игр по убыванию средней оценки:" << std::endl;
    std::vector<BoardGame*> games = {&game1, &game2, &game3};
    

    std::sort(games.begin(), games.end(), [](BoardGame* a, BoardGame* b) {      //лямбда функция, sort принимает указатели на начало и конец и функцию сортировки, в этом случае по убыванию средних оценок
        return *a > *b;
    });
    
    std::cout << "Игры, отсортированные по убыванию средней оценки:" << std::endl;
    for (size_t i = 0; i < games.size(); ++i) {            //warning: comparison between signed and unsigned integer expressions - чтобы этого не произошло - size_t - беззнаковый тип
        std::cout << (i + 1) << ". " << games[i]->getName() 
                  << " (оценка: " << games[i]->getAverageRating() << ")" << std::endl;
    }
    

    std::cout << "\n6. Тестирование получения признаков:" << std::endl;
    std::cout << "Жанр " << game1.getName() << ": " << game1.getFeature("Жанр") << std::endl;
    std::cout << "Есть ли у " << game2.getName() << " признак 'Жанр': " 
              << (game2.hasFeature("Жанр") ? "Да" : "Нет") << std::endl;
    std::cout << "Есть ли у " << game3.getName() << " признак 'Тип': " 
              << (game3.hasFeature("Тип") ? "Да" : "Нет") << std::endl;
    
    std::cout << "\n=== Тестирование завершено ===" << std::endl;
    
    return 0;
}
