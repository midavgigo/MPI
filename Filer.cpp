#include "Filer.h"
void check_dir(std::string dir){
    DWORD ftyp = GetFileAttributesA(dir.c_str());
    if(CreateDirectoryA(dir.c_str(), NULL)){
        std::cout<<dir<<" directory created\n";
    }else{
        std::cout<<"Error in creating "<<dir<<" directory\n";
    }
}

int getDurationFromFile(std::string path){
    std::ifstream in(path);
    int ret = 0;
    if (in.is_open()){
        std::string line;
        getline(in, line);
        ret = atoi(line.c_str());
    }
    in.close();
    return ret;
}

Playlist Filer::makePlaylistFromFile(std::string path){
    int l = 0, r = 0;
    for(int i = 0; i < path.size(); i++){
        if(path[i] == '/' || path[i] == '\\'){
            l = i+1;
        }
        if(path[i] == '.'){
            r = i;
            break;
        }
    }
    std::string name = path.substr(l, r-l);
    std::ifstream in(path);
    Playlist *pl;
    if (in.is_open()){
        std::string line;
        getline(in, line);
        auto pos = songs->find(line);
        Song temp("",0);
        if(pos == songs->end()){
            std::cout<<line<<" don't exist in the collection\n";
        }else{
            temp = pos->second;
        }
        pl = new Playlist((char *)name.c_str(), temp);
        while(getline(in, line)){
            pos = songs->find(line);
            if(pos == songs->end()){
                std::cout<<line<<" don't exist in the collection\n";
            }else{
                pl->AddSong(pos->second);
            }
        }
    }
    in.close();
    return *pl;
}

void Filer::readCollection(){
    std::string path = "files/songs";
    for(const auto & entry : std::filesystem::directory_iterator(path)){
        std::string filename = entry.path().stem().string();
        if(entry.path().extension().string() != ".swf"){
            continue;
        }
        songs->insert(std::pair<std::string, Song>(filename, Song((char *)filename.c_str(), getDurationFromFile(entry.path().string()))));
    }
    path = "files/playlists";
    for(const auto & entry : std::filesystem::directory_iterator(path)){
        std::string filename = entry.path().stem().string();
        if(entry.path().extension().string() != ".pwf"){
            continue;
        }
        Playlist temp = makePlaylistFromFile(entry.path().string());
        std::string name = temp.getName();
        playlists->insert(std::pair<std::string, Playlist>(name, temp));
    }
}

void Filer::writePlaylist(Playlist pl){
    char res[255] = "files/playlists/";
    strcat(res, pl.getName());
    strcat(res, ".pwf");
    std::ofstream file(res);
    if (!file){
        std::cout<<"Can't make file "<<"files/playlists/"<<pl.getName()<<".pwf"<<" for reading\n";
        return;
    }
    char first[255];
    strcpy(first, pl.getNow().getName());
    file<<pl.getNow().getName()<<"\n";
    pl.Next();
    while(strcmp(pl.getNow().getName(),first) != 0){
        file<<pl.getNow().getName()<<"\n";
        pl.Next();
    }
    file.close();
}

void delFile(char *path){
    if( remove(path) == -1 ){
        std::cout<<"Could not delete "<<path<<"\n";
    }else{
        std::cout<<"Deleted "<<path<<"\n";
    }
}

void Filer::delPlaylist(char *name){
    char res[255] = "files/playlists/";
    strcat(res, name);
    strcat(res, ".pwf");
    delFile(res);
}

Filer::Filer(SONG_MAP *_songs, PLAYLIST_MAP  *_playlists): songs(_songs), playlists(_playlists){
    std::string work = "files";
    std::string pls = "files\\playlists";
    std::string sng = "files\\songs";
    check_dir(work);
    check_dir(pls);
    check_dir(sng);

    readCollection();
}
