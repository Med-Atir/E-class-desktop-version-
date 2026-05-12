cmake_minimum_required(VERSION 4.2)
project(PFM)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Database)
include_directories(Includes)
include_directories(Sources)

add_executable(PFM
        Database/Db.cpp
        Database/Db.h
        Includes/Annonce.h
        Includes/Classe.h
        Includes/Demande.h
        Includes/Devoir.h
        Includes/Document.h
        Includes/Etudiant.h
        Includes/Professeur.h
        Includes/Question.h
        Includes/User.h
        Includes/Vect.h
        Sources/Annonce.cpp
        Sources/Cours.cpp
        Sources/Demande.cpp
        Sources/Devoir.cpp
        Sources/Document.cpp
        Sources/Etudiant.cpp
        Sources/Professeur.cpp
        Sources/Question.cpp
        Sources/User.cpp
        Sources/Vect.cpp)
