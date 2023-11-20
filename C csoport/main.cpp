#include "song.h"
#include "user.h"

#include <fstream>

int main() {
    // Read user data from user.txt
    User user;
    std::ifstream input("user.txt");

    input >> user;
    std::cout << user << std::endl;

    if (user.getId() != 1) {
        throw std::runtime_error("User ID is not 1 as expected!");
    }

    // Add new song
    Song song("Korobeiniki", "HirokazuTanaka", 84);
    user.addToPlaylist(song);

    try {
        user.addToPlaylist(song);
        throw std::runtime_error("Failed to raise exception during add.");
    } catch (std::invalid_argument& e) {
        std::cout << "Successfully prevented adding duplicate song." << std::endl;
    }

    std::cout << "After adding a new song:" << std::endl;
    std::cout << user << std::endl;

    // Remove short songs
    user.removeShortSongsFromPlaylist(50);

    std::cout << "After removing short songs:" << std::endl;
    std::cout << user << std::endl;

    for (auto &song : user.getPlaylist()) {
        if (song.getDuration() < 50) {
            throw std::runtime_error("Failed to remove short songs.");
        }
    }

    // Remove artist
    user.removeArtistFromPlaylist("TobyFox");

    std::cout << "After removing TobyFox:" << std::endl;
    std::cout << user << std::endl;

    for (auto &song : user.getPlaylist()) {
        if (song.getTitle() == "TobyFox") {
            throw std::runtime_error("Failed to remove TobyFox.");
        }
    }

    // Test sorting
    user.sortPlaylistBy(SortOption::BY_DURATION);
    std::cout << "After sorting by duration:" << std::endl;
    std::cout << user << std::endl;

    user.sortPlaylistBy(SortOption::BY_ARTIST);
    std::cout << "After sorting by artist:" << std::endl;
    std::cout << user << std::endl;

    user.sortPlaylistBy(SortOption::BY_TITLE);
    std::cout << "After sorting by title:" << std::endl;
    std::cout << user << std::endl;

    // Test copy
    std::cout << "Song 1 title: " << song.getTitle() << std::endl;

    Song song2 = song;
    Song song3(song);
    std::cout << "Song 2 title: " << song2.getTitle() << std::endl;
    std::cout << "Song 3 title: " << song3.getTitle() << std::endl;

    // Test move
    Song song4 = std::move(song);
    Song song5(std::move(song2));
    std::cout << "Song 4 title: " << song4.getTitle() << std::endl;
    std::cout << "Song 5 title: " << song5.getTitle() << std::endl;

    return 0;
}