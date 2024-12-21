#include "PasswordManager.h"
#include <iostream>

int main() {

  try {
    PasswordManager pm("passwords.in");
    std::cout << "Jelszavak betöltve.\n";

    // Műveletek tesztelése
    std::cout << "\n--- Jelszavak listázása (rejtve) ---\n";
    pm.listPasswords(false);

    std::cout << "\n--- Új jelszó hozzáadása ---\n";
    pm.addOrUpdatePassword("LinkedIn", "S3cur3P@ssw0rd!");
    pm.listPasswords(true);

    std::cout << "\n--- Új jelszó hozzáadása (hibás jelszó estén) ---\n";
    try {
      pm.addOrUpdatePassword("WrongPass", "easypassword");
    } catch (const std::exception &e) {
      std::cerr << "Hiba: " << e.what() << "\n";
    }

    std::cout << "\n--- Jelszó lekérdezése ---\n";
    std::cout << "LinkedIn jelszó: " << pm.getPassword("LinkedIn") << "\n";

    std::cout << "\n--- Jelszó törlése ---\n";
    pm.deletePassword("LinkedIn");
    pm.listPasswords(true);

    std::cout << "\n--- Véletlenszerű jelszógenerálás ---\n";
    std::cout << "Generált jelszó: " << pm.generatePassword() << "\n";
  } catch (const std::exception &e) {
    std::cerr << "Hiba: " << e.what() << "\n";
  }

  return 0;
}