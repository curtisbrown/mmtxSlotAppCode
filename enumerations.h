#ifndef ENUMERATIONS_H
#define ENUMERATIONS_H

#include <QObject>
#include <QMetaType>

class Enums : public QObject {
    Q_OBJECT
    Q_ENUMS(Customer)
public:
    enum UutModel {
        UUT_NONE = -1,
        UUT_CM_MERCURY
    };

    enum Button {
        NumberOfButtons	// This should be the last element of the enumeration. Used for the translation array
    };

    enum Language {
        LANG_English,
        LANG_French
    };

    enum StatusMessage {
        STATUS_PASS,
        STATUS_FAIL,
        STATUS_MESSAGE,
        STATUS_DEFAULT
    };

    enum Platform {
        PLATFORM_UNSET,
        PLATFORM_CMTX3,
        PLATFORM_CMTX5
    };

    enum Customer {
        CUSTOMER_UNSET,
        CUSTOMER_BT,
        CUSTOMER_VIRGIN,
        CUSTOMER_MAGYAR_TELEKOM
    };

    enum CabeleModemTest {
        TEST_BOOT
    };
};

#endif // ENUMERATIONS_H
