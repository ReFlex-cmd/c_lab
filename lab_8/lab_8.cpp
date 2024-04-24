#include "User.h"
#include "User.cpp"
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>

// Функция для поиска хэш-значений пользователя по полному имени
std::unordered_map<std::string, int>
findHashCountsByFullName(const std::vector<User> &users, const std::string &full_name) {
    // Извлекаем имя, фамилию и отчество из полного имени
    size_t pos = full_name.find(' '); // Находим позицию первого пробела
    std::string first_name = full_name.substr(0, pos); // Извлекаем имя
    size_t pos2 = full_name.find(' ', pos + 1); // Находим позицию второго пробела
    std::string last_name = full_name.substr(pos + 1, pos2 - pos - 1); // Извлекаем фамилию
    std::string patronymic = full_name.substr(pos2 + 1); // Извлекаем отчество

    // Используем map для хранения хэш-значений и их количества
    std::unordered_map<std::string, int> hash_counts;

    // Проходимся по пользователям
    for (const auto &user: users) {
        // Проверяем, совпадают ли хэш-значения каждого поля с соответствующим полем полного имени
        if (user.getHashFirstName() == user.hashString(first_name) &&
            user.getHashLastName() == user.hashString(last_name) &&
            user.getHashPatronymic() == user.hashString(patronymic)) {
            std::string hash = user.getHashFirstName(); // Получаем хэш-значение
            hash_counts[hash]++; // Увеличиваем счетчик для этого хэша
        }
    }

    return hash_counts; // Возвращаем map с количеством хэшей
}


int main() {
    std::vector<User> users;

    // Создаем экземпляры класса User с разными именами
    User Amelia("Amelia", "Jones", "Brown"); // Amelia Jones Brown
    User Benjamin("Benjamin", "Davis", "Wilson"); // Benjamin Davis Wilson
    User Chloe("Chloe", "Garcia", "Miller"); // Chloe Garcia Miller
    User Daniel("Daniel", "Rodriguez", "Moore"); // Daniel Rodriguez Moore
    User Emily("Emily", "Williams", "Taylor"); // Emily Williams Taylor
    User Grace("Grace", "Hernandez", "Thomas"); // Grace Hernandez Thomas
    User Henry("Henry", "Lopez", "Jackson"); // Henry Lopez Jackson
    User Isabella("Isabella", "Gonzalez", "White"); // Isabella Gonzalez White
    User Jacob("Jacob", "Lee", "Harris"); // Jacob Lee Harris
    User Jacob2("Jacob", "Lee", "Harris"); // Jacob Lee Harris (There are two users with the same name)
    User Frederick("Frederick", "Martinez", "Anderson"); // Frederick Martinez Anderson
    User Frederick2("Frederick", "Martinez",
                    "Anderson"); // Frederick Martinez Anderson (There are two users with the same name)
    User Frederick3("Frederick", "Martinez",
                    "Anderson"); // Frederick Martinez Anderson (There are three users with the same name)


    // Хэшируем каждое поле отдельно для каждого пользователя
    Amelia.hashFields();
    Benjamin.hashFields();
    Chloe.hashFields();
    Daniel.hashFields();
    Emily.hashFields();
    Grace.hashFields();
    Henry.hashFields();
    Isabella.hashFields();
    Jacob.hashFields();
    Jacob2.hashFields();
    Frederick.hashFields();
    Frederick2.hashFields();
    Frederick3.hashFields();


    // Добавляем пользователей в вектор
    users.push_back(Amelia);
    users.push_back(Benjamin);
    users.push_back(Chloe);
    users.push_back(Daniel);
    users.push_back(Emily);
    users.push_back(Grace);
    users.push_back(Henry);
    users.push_back(Isabella);
    users.push_back(Jacob);
    users.push_back(Jacob2);
    users.push_back(Frederick);
    users.push_back(Frederick2);
    users.push_back(Frederick3);


    // Отображаем хэш-значения для имени каждого пользователя
    std::cout << "Hash value for Amelia: " << Amelia.getHashFirstName() << std::endl;
    std::cout << "Hash value for Benjamin: " << Benjamin.getHashFirstName() << std::endl;
    std::cout << "Hash value for Chloe: " << Chloe.getHashFirstName() << std::endl;
    std::cout << "Hash value for Daniel: " << Daniel.getHashFirstName() << std::endl;
    std::cout << "Hash value for Emily: " << Emily.getHashFirstName() << std::endl;
    std::cout << "Hash value for Grace: " << Grace.getHashFirstName() << std::endl;
    std::cout << "Hash value for Henry: " << Henry.getHashFirstName() << std::endl;
    std::cout << "Hash value for Isabella: " << Isabella.getHashFirstName() << std::endl;
    std::cout << "Hash value for Jacob: " << Jacob.getHashFirstName() << std::endl;
    std::cout << "Hash value for Jacob2: " << Jacob2.getHashFirstName() << std::endl;
    std::cout << "Hash value for Frederick: " << Frederick.getHashFirstName() << std::endl;
    std::cout << "Hash value for Frederick2: " << Frederick2.getHashFirstName() << std::endl;
    std::cout << "Hash value for Frederick3: " << Frederick3.getHashFirstName() << std::endl;


    std::string full_name = "Jacob Lee Harris";
    // Находим пользователей с заданным полным именем и подсчитываем их хэши
    std::unordered_map<std::string, int> hash_counts = findHashCountsByFullName(users, full_name);

    // Отображаем результат
    if (hash_counts.empty()) {
        std::cout << "No user found with the name '" << full_name << "'." << std::endl;
    } else {
        for (const auto &pair: hash_counts) {
            std::string hash = pair.first;
            int count = pair.second;
            if (count == 1) {
                std::cout << "Hash value for user " << full_name << ": " << hash << std::endl;
            } else {
                std::cout << count << " users named " << full_name << " found with the same name and hash: " << hash
                          << std::endl;
            }
        }
    }

    return 0;
}
