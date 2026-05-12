//Created by Mohammed atir on 11/05/2026
//IA S4 / Groupe 1
#include "DB.h"
#include <QDebug>

DB::DB() {
    // On spécifie qu'on utilise le driver SQLite
    db = QSqlDatabase::addDatabase("QSQLITE");
}

DB::~DB() {
    disconnect();
}

bool DB::connect(const QString& dbName) {
    db.setDatabaseName(dbName);

    if (!db.open()) {
        qDebug() << "Erreur critique : Impossible d'ouvrir la base de donnees ->" << db.lastError().text();
        return false;
    }
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON;");
    qDebug() << "Succes : Connecte a la base de données SQLite.";
    return true;
}

void DB::disconnect() {
    if (db.isOpen()) {
        db.close();
        qDebug() << "Base de donnees déconnectee.";
    }
}