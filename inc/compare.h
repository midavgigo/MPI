#ifndef __COMPARE_H__
#define __COMPARE_H__


struct compare_str{
    bool operator()(char const *a, char const *b) const{
        return std::strcmp(a, b) < 0;
    }
};

#endif
