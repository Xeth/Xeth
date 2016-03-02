#include <QFileInfo>
#include <QString>
#include <QDir>
#include <QDebug>
#include <QTextStream>
#include <QFile>


QString MakePath(const QString &);
void MakeDirectory(const QString &);
void WriteFile(const QString &path, const QString &content);
