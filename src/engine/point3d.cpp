#include "point3d.h"

#include <QScriptEngine>
#include <QStringList>

#include "gameexception.h"
#include "util.h"


Point3D::Point3D(int x, int y, int z) :
    x(x),
    y(y),
    z(z) {
}

bool Point3D::operator==(const Point3D &other) const {

    return other.x == x && other.y == y && other.z == z;
}

bool Point3D::operator!=(const Point3D &other) const {

    return other.x != x || other.y != y || other.z != z;
}

Point3D Point3D::operator+(const Vector3D &vector) const {

    return Point3D(x + vector.x, y + vector.y, z + vector.z);
}

Point3D Point3D::operator-(const Vector3D &vector) const {

    return Point3D(x - vector.x, y - vector.y, z - vector.z);
}

Vector3D Point3D::operator-(const Point3D &other) const {

    return Vector3D(x - other.x, y - other.y, z - other.z);
}

QString Point3D::toString() const {

    return QString("( %1, %2, %3 )").arg(x).arg(y).arg(z);
}

QString Point3D::toUserString(const Point3D &point) {

    return point.toString();
}

void Point3D::fromUserString(const QString &string, Point3D &point) {

    if (!string.startsWith(QLatin1String("(")) || !string.endsWith(QLatin1String(")"))) {
        throw GameException(GameException::InvalidPoint);
    }

    QStringList stringList = Util::splitComponents(string);
    if (stringList.length() != 3) {
        throw GameException(GameException::InvalidPoint);
    }

    point.x = stringList[0].toInt(),
    point.y = stringList[1].toInt(),
    point.z = stringList[2].toInt();
}

QString Point3D::toJsonString(const Point3D &point, Options options) {

    Q_UNUSED(options)

    return QString("[ %1, %2, %3 ]").arg(point.x).arg(point.y).arg(point.z);
}

void Point3D::fromVariant(const QVariant &variant, Point3D &point) {

    QVariantList variantList = variant.toList();
    if (variantList.length() != 3) {
        throw GameException(GameException::InvalidPoint);
    }

    point.x = variantList[0].toInt();
    point.y = variantList[1].toInt();
    point.z = variantList[2].toInt();
}

QScriptValue Point3D::toScriptValue(QScriptEngine *engine, const Point3D &point) {

    QScriptValue object = engine->newArray(3);
    object.setProperty(0, point.x);
    object.setProperty(1, point.y);
    object.setProperty(2, point.z);
    return object;
}

void Point3D::fromScriptValue(const QScriptValue &object, Point3D &point) {

    point.x = object.property(0).toInt32();
    point.y = object.property(1).toInt32();
    point.z = object.property(2).toInt32();
}
