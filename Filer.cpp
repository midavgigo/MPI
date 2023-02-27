#include "Filer.h"
void check_dir(char *dir){
    DWORD ftyp = GetFileAttributesA(dir);
    if(!(ftyp&FILE_ATTRIBUTE_DIRECTORY)){
        if(CreateDirectoryA(dir, NULL)){
            std::cout<<dir<<" directory created\n";
        }else{
            std::cout<<"Error in creating "<<dir<<" directory\n";
        }
    }else{
        std::cout<<dir<<" directory already exist\n";
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
        if(path[i] == '/'){
            l = i+1;
        }
        if(path[i] == '.'){
            r = i;
            break;
        }
    }
    std::string name = path.substr(l, r-l-1);
    std::ifstream in(path);
    Playlist *pl;
    if (in.is_open()){
        std::string line;
        getline(in, line);
        auto pos = songs->find((char*)line.c_str());
        Song temp("",0);
        if(pos == songs->end()){
            std::cout<<line<<"  don't exist in the collection\n";
        }else{
            temp = pos->second;
        }
        pl = new Playlist((char *)name.c_str(), temp);
        while(getline(in, line)){
            pos = songs->find((char*)line.c_str());
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
        songs->insert(std::pair<char *, Song>((char *)filename.c_str(), Song((char *)filename.c_str(), getDurationFromFile(entry.path().string()))));
    }
    path = "files/playlists";
    for(const auto & entry : std::filesystem::directory_iterator(path)){
        std::string filename = entry.path().stem().string();
        if(entry.path().extension().string() != ".pwf"){
            continue;
        }
        Playlist temp = makePlaylistFromFile(entry.path().string());
        playlists->insert(std::pair<char *, Playlist>((char *)temp.getName(), temp));
    }
}

void Filer::writePlaylist(Playlist *pl){
    char res[255] = "files/playlists/";
    strcat(res, pl->getName());
    strcat(res, ".pwf");
    std::ofstream file(res);
    if (!file){
        std::cout<<"Can't make file "<<"files/playlists/"<<pl->getName()<<".pwf"<<" for reading\n";
    }
    char* first =(char *) pl->getNow().getName();
    file<<pl->getNow().getName()<<"\n";
    pl->Next();
    while(strcmp(pl->getNow().getName(),first)){
        file<<pl->getNow().getName()<<"\n";
    }
    file.close();
}

void Filer::copySongFrom(std::string path){
    for(const auto & entry : std::filesystem::directory_iterator(path)){
        if(entry.path().extension().string() != ".swf"){
            continue;
        }
        std::filesystem::copy(entry.path(), "files/songs/");
    }
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
    delFile(res);
}

void Filer::delSong(char *name){
    char res[255] = "files/songs/";
    strcat(res, name);
    delFile(res);
}

Filer::Filer(std::map<char *, Song, compare_str> *_songs, std::map<char *, Playlist, compare_str>  *_playlists){
    songs = _songs;
    playlists = _playlists;
    char *work = "files";
    char *pl = "files/playlists";
    char *sngs = "files/playlists";
    check_dir(work);
    check_dir(pl);
    check_dir(sngs);

    readCollection();
}
