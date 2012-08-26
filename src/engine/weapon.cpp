#include "weapon.h"


#define super StatsItem

Weapon::Weapon(Realm *realm, uint id, Options options) :
    super(realm, "weapon", id, options) {

    setPortable(true);
}

Weapon::~Weapon() {
}

void Weapon::setHitMessages(const CombatMessageList &hitMessages) {

    if (m_hitMessages != hitMessages) {
        m_hitMessages = hitMessages;

        setModified();
    }
}

void Weapon::setMissMessages(const CombatMessageList &missMessages) {

    if (m_missMessages != missMessages) {
        m_missMessages = missMessages;

        setModified();
    }
}