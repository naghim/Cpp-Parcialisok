#ifndef SONG_H
#define SONG_H

#include <string>

class Song {
public:
    // Constructors
    Song();
    Song(const std::string &title, const std::string &artist, int duration);

    Song(const Song &other);
    Song(Song &&other);

    // Assignment operators
    Song& operator=(const Song &other);
    Song& operator=(Song &&other); 

    // Getter methods
    std::string getTitle() const;
    std::string getArtist() const;
    int getDuration() const;
    int getMinutes() const;
    int getSeconds() const;

    // Equality operator overloading
    bool operator==(const Song &other);

    // Inserter operator
    friend std::ostream& operator<<(std::ostream &os, const Song &song);

    // Extractor operator
    friend std::istream& operator>>(std::istream &is, Song &song);

private:
    // Helper methods
    std::string padNumber(int number) const;

    std::string title;
    std::string artist;
    int duration; 
};

#endif /* SONG_H */
