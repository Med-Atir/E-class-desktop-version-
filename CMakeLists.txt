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
        GUI/Includes/classesPage.h
        GUI/Includes/annoncesPage.h
        GUI/Includes/demandesPage.h
        GUI/Includes/devoirsPage.h
        GUI/Includes/home.h
        GUI/Includes/dashboard.h
        GUI/Includes/loginwindow.h
        GUI/Includes/parametres.h
        GUI/Includes/questionsPage.h
        GUI/Includes/signupwindow.h
        GUI/Sources/classesPage.cpp
        GUI/Sources/annoncesPage.cpp
        GUI/Sources/dashboard.cpp
        GUI/Sources/demandesPage.cpp
        GUI/Sources/devoirsPage.cpp
        GUI/Sources/home.cpp
        GUI/Sources/loginwindow.cpp
        GUI/Sources/parametres.cpp
        GUI/Sources/questionsPage.cpp
        GUI/Sources/signupwindow.cpp
        GUI/UI/classesPage.ui
        GUI/UI/Dashboard.ui
        GUI/UI/demandesPage.ui
        GUI/UI/devoirsPage.ui
        GUI/UI/home.ui
        GUI/UI/parametres.ui
        GUI/UI/questionsPage.ui
        GUI/UI/signupwindow.ui
)
target_link_libraries(PFM PRIVATE Qt6::Sql Qt6::Widgets)