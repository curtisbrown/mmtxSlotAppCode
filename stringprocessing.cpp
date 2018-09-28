#include <iostream>
#include <QFile>
#include <QProcess>
#include <QTextStream>
#include <QDebug>
#include <QHostAddress>
#include <QDir>

#include "stringprocessing.h"

const QString StringProcessing::m_pattern = "\\b(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\b";

/*!
 * \brief isPattern will try to find the pattern in label
 * \param label Label to match the patern with
 * \param pattern Should be a regularexpression
 * \return true if the regular expression defined by the pattern was found in label
 */
bool StringProcessing::isPattern(const QString &label, const QString &pattern)
{
    QRegularExpression re(pattern);
    QRegularExpressionMatch match = re.match(label);
    return  match.hasMatch();
}

/*!
 * \brief StringProcessing::isAlphaNum
 * \return True if string is and alphanumeric string from the begining to the end
 * false otherwise
 */
bool StringProcessing::isAlphaNum(const QString &string) {
    return isPattern(string, "^[0-9a-zA-Z]*$");
}

/*!
 * \brief isMACAddress Checks if label is matching our definition of a MAC address as define with the MAC_REGEX macro.
 * \param label Label to test
 * \return True if label is a MAC address, false otherwise
 */
bool StringProcessing::isMACAddress(const QString &label)
{
    return (isPattern(label, "(([0-9A-Fa-f]{2}[-:]){5}[0-9A-Fa-f]{2})|(([0-9A-Fa-f]{4}.){2}[0-9A-Fa-f]{4})|([0-9A-Fa-f]{12})")
            || isPattern(label, "((([0-9A-Fa-f]{2})|[1-9A-Fa-f])[-:]){5}([0-9A-Fa-f]{2}|[1-9A-Fa-f])"));
}

/*!
 * \brief extractPattern Extracts the substring matching the pattern from a given string
 * \param label Label to extract a pattern from
 * \param pattern Regular expression identifying the pattern to extract
 * \return A QString matching the pattern from the label
 */
QString StringProcessing::extractPattern(const QString &label, const QString &pattern)
{
    QRegularExpression re(pattern);
    QRegularExpressionMatch match = re.match(label);
    return match.captured();
}

/*!
 * \brief extractMAC Removes ':' or '.' from the label
 * \param label
 * \return
 */
QString StringProcessing::extractMAC(QString label)
{
    QRegExp regEx;
    QString macRegex = "(([0-9A-Fa-f]{2}[-:]){5}[0-9A-Fa-f]{2})|(([0-9A-Fa-f]{4}.){2}[0-9A-Fa-f]{4})|([0-9A-Fa-f]{12})";
    if (isPattern(label, macRegex)) {
        label = extractPattern(label, macRegex);
        // \w matches a word character (alphanumeric or _), not just [0-9a-zA-Z_] but also digits and characters from non-roman scripts
        // \W is a negated \w; it represents any non-word character [^\w]
        regEx.setPattern("[\\W]");
        label.replace(regEx, "");
        label = label.toLower();
    } else if (isPattern(label, "((([0-9A-Fa-f]{2})|[1-9A-Fa-f])[-:]){5}([0-9A-Fa-f]{2}|[1-9A-Fa-f])")) {
        // Inserting '0' before
        regEx.setPattern("(\\b)([1-9A-Fa-f])(\\b)");
        label.replace(regEx, "\\10\\2\\3");
        // Extracting the MAC only
        label = extractMAC(label);
    }

    return label;
}

/*!
 * \brief extractIp Takes the IP from the text
 * \param line
 * \return
 */
QString StringProcessing::extractIp(const QString &text, const QString &pattern)
{
    QString ip = extractPattern(text, pattern);
    return ip;
}


void StringProcessing::dumpToFile(const QString &content, const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        out << content;
    }
    file.close();
}

void StringProcessing::createFolder(const QString &folderPath)
{
    QDir dir(folderPath);
    if (!dir.exists())
        dir.mkpath(".");
}
