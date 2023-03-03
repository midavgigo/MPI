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
#define SONG_MAP std::map<std::string, Song>
#define PLAYLIST_MAP std::map<std::string, Playlist>

class Filer{
private:
    SONG_MAP *songs;
    PLAYLIST_MAP *playlists;
protected:
    Filer(SONG_MAP *_songs, PLAYLIST_MAP *_playlists);
    void readCollection();
    void writePlaylist(Playlist pl);
    void delPlaylist(char *name);
    Playlist makePlaylistFromFile(std::string path);
    friend class MPI;
};

#endif
