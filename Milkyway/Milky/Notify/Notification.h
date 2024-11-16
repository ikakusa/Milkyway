#pragma once
#include <Libraries.h>

struct Notification {
	float duration;
	std::string title;
	std::string message;
	bool init = false;
	vec2 pos;

	Notification(float duration, std::string title, std::string message) {
		this->duration = duration;
		this->title = title;
		this->message = message;
	};
};

extern class Notify notify;
class Notify {
public:
	std::vector<Notification*> notifs;
public:
	static void addNotify(Notification* notif) {
		notify.notifs.push_back(notif);
	};
	void drawNotifications(ImDrawList* d);
};