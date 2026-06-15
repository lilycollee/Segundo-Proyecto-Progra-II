#include <random>
#include <ctime>
#include "Android.h"

Android::Android(std::string name_, Type type_) : name(name_), type(type_), inOff(false) {
	setDamageRangeType();
}

Android::~Android() {};

void Android::setDamageRangeType() {
	switch (type) {
        case Type::Easy:
            minDamage = 1;  maxDamage = 5.99;
            break;
        case Type::Medium:
            minDamage = 6; maxDamage = 10.99;
            break;
        case Type::Hard:
            minDamage = 9; maxDamage = 14.99;
            break;
    }
}

bool Android::isOff() const { return inOff; }
void Android::turnOff() { inOff = true; }

double Android::getMinDamage() const { return minDamage; }
double Android::getMaxDamage() const { return maxDamage; }
Android::Type Android::getType() const { return type; }

void Android::attack(double& damage) {
    static std::mt19937 gen(std::time(nullptr));
    std::uniform_real_distribution<double> dist(minDamage, maxDamage);
    damage = dist(gen);
}

std::string Android::getName() const { return name; }

std::string Android::showEntity() const {
	char c;
	(inOff)? c = 'x' : c = char(248);
    std::stringstream ss;
    ss<< "  (" << c << ") " << std::endl;
    ss<<R"( /| |\)" << std::endl;
    ss<<"  ^ ^" << std::endl;

    return ss.str();

}

/* Android:
*	on			  off
 *  (°)			  (x)
 * /| |\		 /| |\
 *  ^ ^			  ^ ^
 */

