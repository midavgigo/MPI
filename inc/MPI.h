#ifndef __CONTAINER_H__
#define __CONTAINER_H__
#include <Song.h>
#include <Playlist.h>
#include <map>
#include "Filer.h"
#include <cstring>
#include <Player.h>

class MPI{
private:
    SONG_MAP songs;
    PLAYLIST_MAP playlists;
    Filer filer = Filer(&songs, &playlists);
    Player pl;
public:
    MPI();
    void editPlaylist(Playlist plst);
    SONG_MAP getSongsCollection();
    PLAYLIST_MAP getPlaylistsCollection();
    bool delPlaylist(char *name);
    void setPlaylistToPlayer(Playlist *plst);
    void pausePlayer();
    void playPlayer();
    bool delSong(Playlist *plst, Song sng);
    bool delSong(Playlist *plst, char *name);
    ~MPI();
};

#endif
