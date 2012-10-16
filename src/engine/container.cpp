#include "container.h"


#define super Item

Container::Container(Realm *realm, uint id, Options options) :
    super(realm, "container", id, options) {
}

Container::~Container() {
}

void Container::addItem(const GameObjectPtr &item) {

    if (!m_items.contains(item)) {
        m_items.append(item);

        adjustWeight(item.cast<Item *>()->weight());
    }
}

void Container::removeItem(const GameObjectPtr &item) {

    if (m_items.removeOne(item)) {
        adjustWeight(-item.cast<Item *>()->weight());
    }
}

void Container::setItems(const GameObjectPtrList &items) {

    if (m_items != items) {
        m_items = items;

        if (mayReferenceOtherProperties()) {
            int weight = 0;
            for (const GameObjectPtr &item : items) {
                weight += item.cast<Item *>()->weight();
            }
            setWeight(weight);
        }

        setModified();
    }
}
