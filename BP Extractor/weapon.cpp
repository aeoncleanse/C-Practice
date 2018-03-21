// Weapon class implementation

#include "weapon.h"

using namespace std;

Weapon::Weapon() {
}

double Weapon::calculateSalvoDamage(int muzzleSalvoSize) {
    double damage;
    if(Numbers.count("BeamLifetime")) {
        if(Numbers["BeamLifetime"] > 0) { // Single shot beam
            int pulseCount = 1 + floor(Numbers["BeamLifetime"] / (Numbers["BeamCollisionDelay"] + 0.1));
            damage = Numbers["Damage"] * pulseCount * muzzleSalvoSize;
        } else if(Booleans["ContinuousBeam"]) {
            damage = Numbers["Damage"];
        }
    } else {
        damage = Numbers["Damage"] * muzzleSalvoSize;
    }

    return damage;
}

int Weapon::calculateDPS() {
    if(!VerifyEssentials()) {
        Error("Essentials missing...");
        return 1;
    }

    int muzzleSalvoSize = Numbers["MuzzleSalvoSize"];
    if(muzzleSalvoSize == 1) { // Muzzles fire together
        for(auto k : Racks) {
            muzzleSalvoSize = max(muzzleSalvoSize, k.second);
        }
    }
    double damagePerSalvo = calculateSalvoDamage(muzzleSalvoSize);

    DPS = damagePerSalvo / round(1 / Numbers["RateOfFire"]);

    return 0;
}

bool Weapon::VerifyEssentials() {
    if(!Numbers.count("Damage") || !Numbers.count("MuzzleSalvoSize") || !Numbers.count("RateOfFire")) {
        return false;
    }
    return true;
}
