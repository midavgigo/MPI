# MPI - Интерфейс для playlist_module
Для работы потребуется собранная версия playlist_module https://github.com/midavgigo/playlist_module/tree/main<br/>
Файл, который нужно подключить, для работы с интерфейсом: inc/MPI.h

## MPI.h

### Методы
void editPlaylist(Playlist plst) - Изменяет плейлист с таким же именем, что и у plst, на plst </br>
std::map<std::string, Song> getSongsCollection() - Возвращает map со всеми песнямив коллекции </br>
std::map<std::string, Playlist> getPlaylistsCollection() - Возвращает map со всеми созданными плейлистами </br>
bool delPlaylist(char *name) - Удаляет плейлист с именем name. Возвращает результат удаления </br>
void setPlaylistToPlayer(Playlist *plst) - Устанавливает в плеер плейлист по указателю </br>
void pausePlayer() - Приостанавливает плеер </br>
void playPlayer() - Возобновляет работу плеера </br>
bool delSong(Playlist *plst, Song sng) - Удаляет песню song из плейлиста plst. Возвращает результат удаления </br>
bool delSong(Playlist *plst, char *name) - Аналог прошлого метода, только удаление по имени </br>

### Пример кода (В дирректории с плейлистами и песнями есть рабочие файлы)

```c++
#include <iostream>
#include "MPI.h"

int main(){
    MPI cont;//Создаем экземпляр класса
    PLAYLIST_MAP plmap = cont.getPlaylistsCollection();//Получаем map с плейлистами
    cont.setPlaylistToPlayer(&plmap["playlist"]);//Передаем в плеер плейлист с именем playlist
    cont.playPlayer();//Запускаем плеер
    char x;
    std::cin>>x;//Пока не будет введен символ плеер будет играть
    return 0;
}
```
[files.zip](https://github.com/midavgigo/MPI/files/10885627/files.zip) - файлы, использованные для примеры(Распокуйте в директории с исполняемым файлом)
