//Created by Mohammed atir on 11/05/2026
//IA S4 / Groupe 1
#ifndef _DB_H_
#define _DB_H_

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QVariant>

class DB {
private:
    QSqlDatabase db;

public:
    DB();
    ~DB();

    // Gestion de la connexion
    bool connect(const QString& dbName);
    void disconnect();
};

#endif // DB_H