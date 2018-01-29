#include <iostream>
#include <string>
#include <stdio.h> 
#include <JSON/json.hpp>
#include <time.h>

#include "Utils.hpp"
#include "Bot.hpp"
// Other includes moved to Bot.hpp

using json = nlohmann::json;

std::string token = "TOKEN";

int masterID{ 52962566 }; // Your Telegram ID here

json dialogs;
json triggers;

void updateHandler(Bot* bot , Update* update) {
	// Check if the update is not a text message
	if (update->message.text == "") {
		// Check if the update is an image
		if (update->message.photosSize > 0) {
			// If so then we can get the photo ID
			bot->sendMessage(update->message.chat.chatID, update->message.photos[update->message.photosSize - 1].photoID);
		}
		return;
	}

	// Check if the bot has been called
	if (lowerCase(update->message.text) == lowerCase(bot->name)) {
		bot->sendChatAction(update->message.chat.chatID, TYPING).fire();
		bot->sendMessage(update->message.chat.chatID, "Dimmi, " + update->message.user.name).fire();

		Log::Action(std::string{ update->message.user.name + " called " + bot->name});
		return;
	}

	// Iterate the triggers, this will be improved in the future
	for (json::iterator it = triggers.begin(); it != triggers.end(); ++it) {
		json::array_t triggers = it.value().get<json::array_t>();
		for (unsigned int i{ 0 }; i < triggers.size(); i++) {
			if (contains(update->message.text, triggers[i].get<std::string>())) {
				json::array_t replies{ dialogs[triggers[i].get<std::string>()].get<json::array_t>() };

				std::string currentReply = replies[rand() % replies.size()];
				if (startsWith(currentReply, "[img]->")) {
					bot->sendChatAction(update->message.chat.chatID, UPLOAD_PHOTO);
					// bot->sendPhoto(update->message.chat.chatID, splitByString(currentReply, "->")[1].c_str());
					return;
				}

				bot->sendChatAction(update->message.chat.chatID, TYPING);
				bot->sendMessage(update->message.chat.chatID, currentReply);
				Log::Action(std::string{ update->message.user.name + ": '" + triggers[i].get<std::string>() + "'."});
				return;
			}
		}
	}

	// Check if the message starts with our bot's name
	if (startsWith(update->message.text, lowerCase(bot->name))) {

		// Check if our trigger is in the message
		if (contains(update->message.text, "rimage", true)) {
			bot->sendChatAction(update->message.chat.chatID, UPLOAD_PHOTO).fire();
			bot->sendPhoto(update->message.chat.chatID, "Icy.jpg", readBytes("resources/images/Icy.jpg")).fire();//std::string{ "resources/images/Icy.jpg" });
			Log::Action(std::string{ update->message.user.name + ": rimage" });
			return; // Don't forget to return to avoid multiple triggers
		}

		if (contains(update->message.text, "document", true)) {
			bot->sendChatAction(update->message.chat.chatID, UPLOAD_DOCUMENT).fire();
			bot->sendDocument(update->message.chat.chatID, "Icy.jpg", readBytes("resources/images/Icy.jpg")).fire();
			Log::Action(std::string{ update->message.user.name + ": rimage" });
			return;
		}
	}
}

void start(Bot* bot, Update* update, std::vector<std::string>* args) {
	bot->sendChatAction(update->message.chat.chatID, TYPING);
	bot->sendMessage(update->message.chat.chatID, "Salve " + update->message.user.name);
}

void reload(Bot* bot, Update* update, std::vector<std::string>* args) {
	dialogs = json::parse(readFile("resources/JSON/dialogs.json"));
	triggers = json::parse(readFile("resources/JSON/triggers.json"));

	bot->sendChatAction(update->message.chat.chatID, TYPING);
	bot->sendMessage(update->message.chat.chatID, "Reloaded.");

	Log::Action(std::string{ update->message.user.name + ": 'reload'." });

	
}

// Get your ID with /myid
void myid(Bot* bot, Update* update, std::vector<std::string>* args) {
	bot->sendChatAction(update->message.chat.chatID, TYPING);
	bot->sendMessage(update->message.chat.chatID, "ID: " + std::to_string(update->message.user.userID));
}

// Example of only-master command
void stop(Bot* bot, Update* update, std::vector<std::string>* args) {
	bot->sendChatAction(update->message.chat.chatID, TYPING);
	if (masterID == update->message.user.userID) {
		bot->sendMessage(update->message.chat.chatID, "Stopping...");
		bot->stopPolling();
	}
	else 
	{
		bot->sendMessage(update->message.chat.chatID, "Only my master can issue this command.");
	}
}

// Just an echo command
void echo(Bot* bot, Update* update, std::vector<std::string>* args) {
	bot->sendChatAction(update->message.chat.chatID, TYPING);
	bot->sendMessage(update->message.chat.chatID, update->message.text);
}


int main() {
	// Initialize random
	srand(time(NULL));

	dialogs = json::parse(readFile("resources/JSON/dialogs.json"));
	triggers = json::parse(readFile("resources/JSON/triggers.json"));

	// Create our bot!
	Bot bot = Bot(token);
	Log::Info(std::string{ "Bot " + bot.name + " started." });

	// Add some handlers
	bot.setUpdateHandler(&updateHandler);
	bot.addCommandHandler("/reload", &reload);
	bot.addCommandHandler("/start", &start);
	bot.addCommandHandler("/myid", &myid);
	bot.addCommandHandler("/stop", &stop);
	bot.addCommandHandler("/echo", &echo);

	Log::Debug("Starting polling...");
	bot.startPolling();
	// This function is blocking, i'll add a thread in the future, maybe...

	return 0;
}

