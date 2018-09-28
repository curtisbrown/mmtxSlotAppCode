#ifndef STRINGPROCESSING_H
#define STRINGPROCESSING_H

#include <QString>
#include <QTextStream>
#include <QRegularExpression>

class StringProcessing {
public:
    static bool isPattern(const QString &label, const QString &pattern);

    static bool isAlphaNum(const QString &string);

    static bool isMACAddress(const QString &label);

    static QString extractPattern(const QString &label, const QString &pattern);

    static QString extractMAC(QString label);

    static QString extractIp(const QString &text, const QString &pattern = m_pattern);

    static void dumpToFile(const QString &content, const QString &fileName);

    static void createFolder(const QString &folderPath);

private:
    static const QString m_pattern;
};


#endif // STRINGPROCESSING_H
