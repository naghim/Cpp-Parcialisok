#include "IPasswordManager.h"
#include <map>
#include <string>

class PasswordManager : public IPasswordManager {
private:
  // Website -> Password
  std::map<std::string, std::string> passwords;

public:
  // The interface did not have a constructor, but the derived class does
  // We load the passwords from the file
  PasswordManager(const std::string &filename);

  // Get password, throws exception if site is not found
  std::string getPassword(const std::string &site) const;
  // Delete password, throws exception if site is not found
  void deletePassword(const std::string &site);
  // List passwords, reveals passwords if reveal = true
  void listPasswords(bool reveal = false) const;
  // Add or update password, throws exception if password is invalid
  void addOrUpdatePassword(const std::string &site,
                           const std::string &password);
  // Generates a random password
  std::string generatePassword(int length = 12);
  // Checks if a password is valid (i.e. it meets security requirements)
  bool isPasswordValid(const std::string &password) const;
};
