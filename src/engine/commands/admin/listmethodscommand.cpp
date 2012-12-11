#include "listmethodscommand.h"

#include <QScriptValueIterator>

#include "scriptengine.h"
#include "util.h"


#define super AdminCommand

ListMethodsCommand::ListMethodsCommand(QObject *parent) :
    super(parent) {

    setDescription("List all JavaScript-accessible methods of an object.\n"
                   "\n"
                   "Usage: list-methods <object-name> [#]");
}

ListMethodsCommand::~ListMethodsCommand() {
}

void ListMethodsCommand::execute(Player *player, const QString &command) {

    super::prepareExecute(player, command);

    GameObjectPtr object = takeObject(currentRoom()->exits() + currentRoom()->characters() +
                                      currentRoom()->items());
    if (!requireSome(object, "Object not found.")) {
        return;
    }

    send(QString("These are all known methods of %1:\n"
                 "\n").arg(Util::highlight(QString("object #%1").arg(object->id()))));

    ScriptEngine *scriptEngine = ScriptEngine::instance();
    QScriptValue value = scriptEngine->evaluate(QString("Object.keys($('%1:%2'))")
                                                .arg(QString(object->objectType().toString()).toLower())
                                                .arg(object->id()));

    QScriptValueIterator it(value);
    while (it.hasNext()) {
        it.next();
        QString key = it.value().toString();
        if (key.contains('(') && !key.startsWith("destroyed(") &&
            !key.contains(QRegExp("[(,]Options\\)"))) {
            key = key.replace("QString", "string").replace("QScriptValue", "value")
                     .replace("GameObjectPtr", "GameObject").replace(",", ", ");
            send(QString("  %1\n").arg(Util::highlight(key)));
        }
    }
}
