#ifndef __CONTAINER_H__
#define __CONTAINER_H__
#include <Song.h>
#include <Playlist.h>
#include <map>
#include "compare.h"
#include "Filer.h"
#include <cstring>

class Container{
private:
    SONG_MAP songs;
    PLAYLIST_MAP playlists;
    Filer filer = Filer(&songs, &playlists);
public:
    Container(){}
    void editPlaylist(Playlist pl);
    SONG_MAP getSongsCollection();
    PLAYLIST_MAP getPlaylistsCollection();
    void delSong(char *name);
    void delPlaylist(char *name);
    void scanSong(std::string path);
    void scanPlaylist(std::string path);
};

#endif
