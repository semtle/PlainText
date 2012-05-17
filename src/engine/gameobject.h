#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QList>
#include <QMetaProperty>
#include <QObject>
#include <QScriptEngine>
#include <QScriptValue>

#include "scriptfunctionmap.h"


class GameObject : public QObject {

    Q_OBJECT

    public:
        enum Options {
            NoOptions = 0x00,
            Copy = 0x01
        };

        explicit GameObject(const char *objectType, uint id, Options options = NoOptions);
        virtual ~GameObject();

        const char *objectType() const { return m_objectType; }
        Q_PROPERTY(const char *objectType READ objectType STORED false)

        const uint id() const { return m_id; }
        Q_PROPERTY(uint id READ id STORED false)

        const QString &name() const { return m_name; }
        virtual void setName(const QString &name);
        Q_PROPERTY(QString name READ name WRITE setName)

        const QString &description() const { return m_description; }
        virtual void setDescription(const QString &description);
        Q_PROPERTY(QString description READ description WRITE setDescription)

        const ScriptFunctionMap &triggers() const { return m_triggers; }
        virtual void setTriggers(const ScriptFunctionMap &triggers);
        Q_PROPERTY(ScriptFunctionMap triggers READ triggers WRITE setTriggers)

        bool save();
        bool load(const QString &path);

        void resolvePointers();

        void setDeleted();

        static GameObject *createByObjectType(const QString &objectType, uint id = 0,
                                              Options options = NoOptions);

        static GameObject *createCopy(const GameObject *other);

        static GameObject *createFromFile(const QString &path);

        static QScriptValue toScriptValue(QScriptEngine *engine, GameObject *const &gameObject);
        static void fromScriptValue(const QScriptValue &object, GameObject *&gameObject);

    protected:
        void setModified();

        Options options() const { return m_options; }

    private:
        const char *m_objectType;
        uint m_id;
        Options m_options;

        QString m_name;
        QString m_description;
        ScriptFunctionMap m_triggers;

        bool m_deleted;

        QList<QMetaProperty> storedMetaProperties() const;
};

Q_DECLARE_METATYPE(GameObject *)

#endif // GAMEOBJECT_H
