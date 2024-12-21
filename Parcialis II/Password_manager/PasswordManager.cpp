#include "PasswordManager.h"
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <regex>
#include <stdexcept>
#include <string>

PasswordManager::PasswordManager(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cout << "Could not open the file named: " << filename;
    return;
  }

  std::string site, password, line;

  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::getline(ss, site, ';');
    std::getline(ss, password);

    passwords[site] = password;
  }

  file.close();
}

std::string PasswordManager::getPassword(const std::string &site) const {
  auto it = passwords.find(site);
  if (it == passwords.end()) {
    throw std::invalid_argument("Site not found!");
  }
  return it->second;
}

void PasswordManager::deletePassword(const std::string &site) {
  if (passwords.erase(site) == 0) {
    throw std::invalid_argument("Site not found!");
  }
}

void PasswordManager::listPasswords(bool reveal) const {
  for (const auto &[site, password] : passwords) {
    std::cout << site << ": "
              << (reveal ? password : std::string(password.length(), '*'))
              << std::endl;
  }
}

void PasswordManager::addOrUpdatePassword(const std::string &site,
                                          const std::string &password) {
  if (!isPasswordValid(password)) {
    throw std::invalid_argument("The password is not valid!");
  }
  passwords[site] = password;
}

std::string PasswordManager::generatePassword(int length) {
  if (length < 8) {
    throw std::invalid_argument("The password length must be at least 8!");
  }

  const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwx"
                            "yz0123456789!@#$%^&*()";
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<> dist(0, chars.size() - 1);

  std::string password;

  while (!isPasswordValid(password)) {
    password.clear();
    for (int i = 0; i < length; ++i) {
      password += chars[dist(rng)];
    }
  }

  return password;
}

bool PasswordManager::isPasswordValid(const std::string &password) const {
  if (password.length() < 8)
    return false;

  bool hasUpper = false, hasLower = false, hasDigit = false;

  for (char c : password) {
    if (std::isupper(c))
      hasUpper = true;
    if (std::islower(c))
      hasLower = true;
    if (std::isdigit(c))
      hasDigit = true;
  }
  return hasUpper && hasLower && hasDigit;
}