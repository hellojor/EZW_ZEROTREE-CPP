#ifndef CSTATUS_H
#define CSTATUS_H

#include <string>

using std::string;

// POS: wij > 0 and abs(wij) >= threshold
// NEG: wij < 0 and abs(wij) >= threshold
// ZTR: abs(wij) < threshold and all the child of subtree < threshold
// HZ : abs(wij) >= threshold and one of the child of subtree >= threshold

enum class CSTATUS {
	NONE = 0,
	POS,
	NEG,
	ZTR,
	HZ
};

string GET_CSTATUS_NAME(CSTATUS s) {
	switch (s) {
	case CSTATUS::POS:
		return "POS";
	case CSTATUS::NEG:
		return "NEG";
	case CSTATUS::ZTR:
		return "ZTR";
	case CSTATUS::HZ:
		return "HZ";
	default:
		return "NAN";
	}
}

#endif // !CSTATUS_H
