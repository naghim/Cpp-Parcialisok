#include <map>
#include <string>

class IPasswordManager {
public:
  // Interfaces don't have constuctors

  // Get password, throws exception if site not found
  virtual std::string getPassword(const std::string &site) const = 0;
  // Delete password, throws exception if site not found
  virtual void deletePassword(const std::string &site) = 0;
  // List passwords, reveals passwords if reveal = true
  virtual void listPasswords(bool reveal = false) const = 0;
  // Add or update password, throws exception if password is invalid
  virtual void addOrUpdatePassword(const std::string &site,
                                   const std::string &password) = 0;
  // Generates a random password
  virtual std::string generatePassword(int length = 12) = 0;
  // Checks if a password is valid (i.e. it meets security requirements)
  virtual bool isPasswordValid(const std::string &password) const = 0;
};