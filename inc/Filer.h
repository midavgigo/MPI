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
    std::map<char *, Song, compare_str> *songs;
    std::map<char *, Playlist, compare_str> *playlists;
    Playlist makePlaylistFromFile(std::string path);
protected:
    Filer(std::map<char *, Song, compare_str> *_songs, std::map<char *, Playlist, compare_str>  *_playlists);
    void readCollection();
    void writePlaylist(Playlist *pl);
    void copySongFrom(std::string path);
    void delPlaylist(char *name);
    void delSong(char *name);
    friend class Container;
};

#endif
