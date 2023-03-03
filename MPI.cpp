#include "MPI.h"

MPI::MPI(){}

MPI::~MPI(){
    pl.stop();
}

void MPI::editPlaylist(Playlist plst){
    playlists[plst.getName()] = plst;
    filer.writePlaylist(plst);
}

SONG_MAP MPI::getSongsCollection(){
    return songs;
}

PLAYLIST_MAP MPI::getPlaylistsCollection(){
    return playlists;
}

bool MPI::delSong(Playlist *plst, char *name){
    if(pl.getPlayingSong() == songs[name]){
        return false;
    }
    return plst->delSong(songs[name]);
}

bool MPI::delSong(Playlist *plst, Song sng){
    if(pl.getPlayingSong() == sng){
        return false;
    }
    return plst->delSong(sng);
}

bool MPI::delPlaylist(char *name){
    Playlist tmp = *pl.getPlaylist();
    if(strcmp(name, tmp.getName())==0){
        return false;
    }
    filer.delPlaylist(name);
    return true;
}

void MPI::setPlaylistToPlayer(Playlist *plst){
    pl.setPlaylist(plst);
}

void MPI::pausePlayer(){
    pl.setState(false);
}

void MPI::playPlayer(){
    pl.setState(true);
}
