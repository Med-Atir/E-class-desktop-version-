//Created by Mohammed atir on 23/05/2026
//IA S4 / Groupe 1
//
// Created by simoa on 23/05/2026.
//

#include "../Includes/Video.h"

Video::Video(const Video &v):Document(v) {
}

Video::~Video() {
}

Video::Video(int id, std::string titre, std::string cheminFichier, QDateTime date, int prof, int cl):Document(id,titre,cheminFichier,date,prof,cl) {
}