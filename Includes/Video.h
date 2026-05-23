//Created by Mohammed atir on 23/05/2026
//IA S4 / Groupe 1

#ifndef _VIDEO_H_
#define _VIDEO_H_
#include "Document.h"

class Video:public Document {
public:
    Video(int id,std::string titre,std::string cheminFichier,QDateTime date,int prof,int cl);
    Video(const Video&);
    ~Video();
};

#endif //Video