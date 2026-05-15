cmake_minimum_required(VERSION 3.16)
project(PFM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include_directories(.)
include_directories(Database)
include_directories(Includes)
include_directories(Sources)
find_package(Qt6 COMPONENTS Sql Widgets REQUIRED)

add_executable(PFM
        Database/Db.cpp
        Database/Db.h
        Includes/Annonce.h
        Includes/Classe.h
        Includes/Demande.h
        Includes/Document.h
        Includes/Devoir.h
        Includes/Etudiant.h
        Includes/Professeur.h
        Includes/Question.h
        Includes/User.h
        Includes/Vect.h
        Sources/Annonce.cpp
        Sources/Demande.cpp
        Sources/Document.cpp
        Sources/Devoir.cpp
        Sources/Etudiant.cpp
        Sources/Professeur.cpp
        Sources/Question.cpp
        Sources/User.cpp
        Sources/Vect.cpp
        Sources/Classe.cpp
        main.cpp
        GUI/Sources/loginwindow.cpp
        GUI/Includes/loginwindow.h
        GUI/UI/loginwindow.ui
        GUI/Sources/signupwindow.cpp
        GUI/Includes/signupwindow.h
        GUI/UI/signupwindow.ui
        GUI/Includes/dashboard.h
        GUI/Sources/dashboard.cpp
        GUI/Sources/dashboard.cpp
        GUI/Sources/classes.cpp
        GUI/Includes/classes.h
        GUI/UI/classes.ui
        GUI/Sources/demandes.cpp
        GUI/Includes/demandes.h
        GUI/UI/demandes.ui
        GUI/Sources/devoirs.cpp
        GUI/Includes/devoirs.h
        GUI/UI/devoirs.ui
        GUI/Sources/questions.cpp
        GUI/Includes/questions.h
        GUI/UI/questions.ui
        GUI/Sources/annonces.cpp
        GUI/Includes/annonces.h
        GUI/UI/annonces.ui
        GUI/Sources/parametres.cpp
        GUI/Includes/parametres.h
        GUI/UI/parametres.ui
        GUI/Sources/home.cpp
        GUI/Includes/home.h
        GUI/UI/home.ui
)
target_link_libraries(PFM PRIVATE Qt6::Sql Qt6::Widgets)