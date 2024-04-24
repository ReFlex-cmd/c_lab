#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string first_name;
    std::string last_name;
    std::string patronymic;
    std::string hash_first_name;
    std::string hash_last_name;
    std::string hash_patronymic;

public:
    User(const std::string &first, const std::string &last, const std::string &pat);

    // Getters and Setters
    std::string getFirstName() const;

    void setFirstName(const std::string &first);

    std::string getLastName() const;

    void setLastName(const std::string &last);

    std::string getPatronymic() const;

    void setPatronymic(const std::string &pat);

    // Hashing Methods
    void hashFields();

    std::string getHashFirstName() const;

    std::string getHashLastName() const;

    std::string getHashPatronymic() const;

    std::string hashString(const std::string &str) const;
};

#endif // USER_H
