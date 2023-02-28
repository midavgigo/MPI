#include "Container.h"
void Container::editPlaylist(Playlist pl){
    filer.writePlaylist(pl);
}

SONG_MAP Container::getSongsCollection(){
    return songs;
}

PLAYLIST_MAP Container::getPlaylistsCollection(){
    return playlists;
}

void Container::delSong(char *name){
    filer.delSong(name);
}

void Container::delPlaylist(char *name){
    filer.delPlaylist(name);
}

void Container::scanSong(std::string path){
    filer.copyFileFrom(path, "files/songs", ".swf");
}

void Container::scanPlaylist(std::string path){
    filer.copyFileFrom(path, "files/playlists", ".pwf");
}
