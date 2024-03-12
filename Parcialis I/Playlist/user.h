#ifndef USER_H
#define USER_H

#include "song.h"

#include <iostream>
#include <vector>
#include <string>

// Enum for sorting options
enum SortOption {
    BY_TITLE,
    BY_ARTIST,
    BY_DURATION
};

class User {
public:
    // Constructors
    User();
    User(const std::string &username);

    User(const User &other);
    User(User &&other);

    // Assignment operators
    User& operator=(const User &other);
    User& operator=(User &&other); 

    // Getter methods
    int getId() const;
    std::string getUsername() const;
    const std::vector<Song> &getPlaylist() const;

    // Playlist management
    void addToPlaylist(const Song &song);
    int removeArtistFromPlaylist(const std::string &artist);
    int removeShortSongsFromPlaylist(int minDuration);

    // Sort playlist by name or price
    void sortPlaylistBy(SortOption option);

    // Inserter operator
    friend std::ostream& operator<<(std::ostream &os, const User &user);

    // Extractor operator
    friend std::istream& operator>>(std::istream &is, User &user);


private:
    int id;
    std::string username;
    std::vector<Song> playlist;

    // First user's ID must be 1
    static int nextId;
};

#endif /* USER_H */