#include "user.h"

#include <algorithm>

int User::nextId = 0;

User::User() {
    this->id = ++User::nextId;
    this->username = "";
}

User::User(const std::string& username) {
    this->id = ++User::nextId;
    this->username = username;
}

// Copy constructor
User::User(const User& other) {
    nextId++;
    this->id = other.id;
    this->username = other.username;
    this->playlist = other.playlist;
}

// Move constructor
User::User(User&& other) {
    nextId++;
    this->id = other.id;
    this->username = other.username;
    this->playlist = other.playlist;

    other.id = 0;
    other.username.clear();
    other.playlist.clear();
}

// Copy assignment
User& User::operator=(const User& other) {
    if (this != &other) {
        this->id = other.id;
        this->username = other.username;
        // this->playlist doesn't need to be cleared beforehand 
        // because it's a vector containing OBJECTS and 
        // it will be cleared when it's destroyed
        // i. e. overwritten by the assignment operator
        this->playlist = other.playlist;
    }
    return *this;

}

// Move assignment
User& User::operator=(User&& other) {
    if (this != &other) {
        this->id = other.id;
        this->username = other.username;
        // this->playlist doesn't need to be cleared beforehand 
        // because it's a vector containing OBJECTS and 
        // it will be cleared when it's destroyed
        // i. e. overwritten by the assignment operator
        this->playlist = other.playlist;

        other.id = 0;
        other.username.clear();
        other.playlist.clear();
    }

    return *this;
}

// Getter method
int User::getId() const {
    return this->id;
}

std::string User::getUsername() const {
    return this->username;
}

const std::vector<Song> &User::getPlaylist() const {
    return this->playlist;
}

// Playlist management
void User::addToPlaylist(const Song& song) {
    if (std::find(this->playlist.begin(), this->playlist.end(), song) == this->playlist.end()) {
        this->playlist.push_back(song);
    } else {
        throw std::invalid_argument("Song already in playlist");
    }
}

int User::removeArtistFromPlaylist(const std::string &artist) {
    // It can be solved with remove_if but considerig that 
    // we are only at week 6, I used the simplest solution I could think of 
    
    bool ok = false;
    int count = 0;

    while (!ok) {
        ok = true;

        for (int i = 0; i < this->playlist.size(); ++i) {
            Song song = this->playlist[i];

            if (song.getArtist() == artist) {
                this->playlist.erase(this->playlist.begin() + i);
                ok = false;
                count++;
                break;
            }
        }
    }

    return count;
}

int User::removeShortSongsFromPlaylist(int minDuration) {
    bool ok = false;
    int count = 0;

    while (!ok) {
        ok = true;

        for (int i = 0; i < this->playlist.size(); ++i) {
            Song song = this->playlist[i];

            if (song.getDuration() < minDuration) {
                this->playlist.erase(this->playlist.begin() + i);
                ok = false;
                count++;
                break;
            }
        }
    }

    return count;
}

// Sort playlist by name or price
void User::sortPlaylistBy(SortOption option) {
    switch (option) {
        case SortOption::BY_TITLE:
            std::sort(this->playlist.begin(), this->playlist.end(), [](const Song& song1, const Song& song2) {
                return song1.getTitle() < song2.getTitle();
            });
            break;
        case SortOption::BY_ARTIST:
            std::sort(this->playlist.begin(), this->playlist.end(), [](const Song& song1, const Song& song2) {
                return song1.getArtist() < song2.getArtist();
            });
            break;
        case SortOption::BY_DURATION:
            std::sort(this->playlist.begin(), this->playlist.end(), [](const Song& song1, const Song& song2) {
                return song1.getDuration() < song2.getDuration();
            });
            break;
    }
}

// Inserter operator
std::ostream& operator<<(std::ostream& os, const User& user) {
    os << user.username << " has " << user.playlist.size() << " songs:" << std::endl;

    for (const Song& song : user.playlist) {
        os << song;
    }

    return os;
}

// Extractor operator
std::istream& operator>>(std::istream &is, User &user) {
    is >> user.username;

    int playlistSize;
    is >> playlistSize;

    for (int i = 0; i < playlistSize; i++) {
        Song song;
        is >> song;

        user.playlist.push_back(song);
    }

    return is;
}