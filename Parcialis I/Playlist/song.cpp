#include "Song.h"
#include <iostream>
#include <string>

Song::Song() {
    this->title = "";
    this->artist = "";
    this->duration = 0;
}

Song::Song(const std::string& title, const std::string& artist, int duration) {
    this->title = title;
    this->artist = artist;
    this->duration = duration;
}

// Copy constructor
Song::Song(const Song& other) {
    this->title = other.title;
    this->artist = other.artist;
    this->duration = other.duration;
}

// Move constructor
Song::Song(Song&& other) {
    this->title = other.title;
    this->artist = other.artist;
    this->duration = other.duration;
    
    other.title.clear();
    other.artist.clear();
    other.duration = 0.0;
}

// Copy assignment operator
Song& Song::operator=(const Song& other) {
    if (this != &other) {
        this->title = other.title;
        this->artist = other.artist;
        this->duration = other.duration;
    }

    return *this;
}

// Move assignment
Song& Song::operator=(Song&& other) {
    if (this != &other) {
        this->title = other.title;
        this->artist = other.artist;
        this->duration = other.duration;

        other.title.clear();
        other.artist.clear();
        other.duration = 0.0;
    }

    return *this;
}

// Getter methods
std::string Song::getTitle() const {
    return this->title;
}

std::string Song::getArtist() const {
    return this->artist;
}

int Song::getDuration() const {
    return this->duration;
}

int Song::getMinutes() const {
    return (int) (this->duration / 60);
}

int Song::getSeconds() const {
    return this->duration % 60;
}

// Equality operator overloading
bool Song::operator==(const Song& other) {
    return this->title == other.title;
}

std::string Song::padNumber(int number) const {
    return number < 10 ? ("0" + std::to_string(number)) : std::to_string(number);
}

// Inserter operator
std::ostream& operator<<(std::ostream& os, const Song& song) {
    os << " - " << song.title << " by " << song.artist << " (" << song.padNumber(song.getMinutes()) << ":" << song.padNumber(song.getSeconds()) << ")" << std::endl;
    return os;
}

// Extractor operator
std::istream& operator>>(std::istream &is, Song &song) {
    is >> song.title >> song.artist >> song.duration;
    return is;
}