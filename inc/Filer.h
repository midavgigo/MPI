#ifndef __FILER_H__
#define __FILER_H__
#include <iostream>
#include <fstream>
#include <DLL.h>
#include <Song.h>
#include <Playlist.h>
#include <Windows.h>
#include <cstring>
#include <filesystem>
#include <map>
#include "compare.h"

class Filer{
private:
    std::map<char *, Song, compare> *songs;
    std::map<char *, Playlist, compare> *playlists;
protected:
    Filer(std::map<char *, Song, compare> *_songs, std::map<char *, Playlist, compare>  *_playlists);
    void readCollection();
    void writePlaylist();
    void scanSong();
    void delPlaylist();
    void delSong();
    friend class Container;
};

#endif
