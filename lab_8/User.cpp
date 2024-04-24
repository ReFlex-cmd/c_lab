#include "User.h"
#include <functional>

User::User(const std::string &first, const std::string &last, const std::string &pat)
        : first_name(first), last_name(last), patronymic(pat) {}

std::string User::hashString(const std::string &str) const {
    std::hash<std::string> hasher;
    return std::to_string(hasher(str));
}

std::string User::getFirstName() const {
    return first_name;
}

void User::setFirstName(const std::string &first) {
    first_name = first;
}

std::string User::getLastName() const {
    return last_name;
}

void User::setLastName(const std::string &last) {
    last_name = last;
}

std::string User::getPatronymic() const {
    return patronymic;
}

void User::setPatronymic(const std::string &pat) {
    patronymic = pat;
}

void User::hashFields() {
    hash_first_name = hashString(first_name);
    hash_last_name = hashString(last_name);
    hash_patronymic = hashString(patronymic);
}

std::string User::getHashFirstName() const {
    return hash_first_name;
}

std::string User::getHashLastName() const {
    return hash_last_name;
}

std::string User::getHashPatronymic() const {
    return hash_patronymic;
}
