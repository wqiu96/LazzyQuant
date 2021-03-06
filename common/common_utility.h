#ifndef COMMON_UTILITY_H
#define COMMON_UTILITY_H

#include <QMetaEnum>
#include <QSet>
#include <QString>
#include <QTime>

#define INVALID_DATE_STRING QStringLiteral("00000000")

#define TM1 \
    QTime _tempt; _tempt.start();
#define TM2 \
    qWarning() << _tempt.elapsed() << "ms";


enum OPTION_TYPE {
    CALL_OPT,
    PUT_OPT,
};

QString getCode(const QString &instrumentID);
bool parseOptionID(const QString &optionID, QString &futureID, OPTION_TYPE &type, int &exercisePrice);
QString makeOptionID(const QString &futureID, OPTION_TYPE type, int exercisePrice);
bool isOption(const QString &instrumentID);
bool isStockLike(const QString &instrumentID);

template<typename EnumType>
QList<int> enumValueToList(int value)
{
    QSet<int> valueSet;
    auto mobj = QMetaEnum::fromType<EnumType>();
    int count = mobj.keyCount();
    for (int i = 0; i < count; i++) {
        int k = mobj.value(i);
        if ((k != 0) && ((value & k) == k)) {
            valueSet.insert(k);
        }
    }
    return valueSet.toList();
}


// 三种类型的订单 (0:普通限价单, 1:Fill and Kill, 2:Fill or Kill)
#define LIMIT_ORDER   0
#define FAK_ORDER     1
#define FOK_ORDER     2

#endif // COMMON_UTILITY_H
