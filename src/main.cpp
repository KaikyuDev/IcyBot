#include <string>
#include <entities/methods/GetMe.hpp>
#include <entities/Update.hpp>
#include <core/Bot.hpp>
#include <entities/methods/SendMessage.hpp>
#include <entities/methods/SendPhoto.hpp>
#include <utils/Utils.hpp>
#include <entities/methods/SendAudio.hpp>
#include <entities/methods/SendDocument.hpp>
#include <entities/methods/SendVideo.hpp>
#include <entities/methods/SendAnimation.hpp>
#include <entities/methods/SendVoice.hpp>
#include <entities/methods/SendVideoNote.hpp>
#include <entities/methods/ForwardMessage.hpp>
#include <entities/methods/SendLocation.hpp>
#include <entities/methods/SendPoll.hpp>
#include <entities/methods/SendChatAction.hpp>
#include <entities/methods/GetUserProfilePhotos.hpp>
#include <entities/File.hpp>
#include <entities/methods/GetFile.hpp>
#include <entities/methods/RestrictChatMember.hpp>
#include <entities/methods/PromoteChatMember.hpp>
#include <entities/methods/SetChatAdministratorCustomTitle.hpp>
#include <entities/methods/ExportChatInviteLink.hpp>
#include <entities/methods/SetChatPhoto.hpp>
#include <entities/methods/DeleteChatPhoto.hpp>
#include <entities/methods/SetChatTitle.hpp>
#include <entities/methods/SetChatDescription.hpp>
#include <entities/methods/PinChatMessage.hpp>
#include <entities/methods/UnpinChatMessage.hpp>
#include <entities/methods/LeaveChat.hpp>
#include <entities/methods/GetChat.hpp>
#include <entities/methods/GetChatAdministrators.hpp>
#include <entities/methods/GetChatMembersCount.hpp>
#include <entities/methods/GetChatMember.hpp>
#include <entities/methods/DeleteChatStickerSet.hpp>
#include <entities/methods/SetChatStickerSet.hpp>

using namespace CppTelegramBots;

void updateHandler(const Bot *bot, const Update *update) {
    Log::Debug("New update from " + update->message.user.firstName);
}

void chatId(const Bot *bot, const Update *update) {
    std::string text = "ID: " + std::to_string(update->message.chat.id);
    long long toChat = update->message.chat.id;
    long messageId = update->message.messageId;

    BaseResponse<Message> response = bot->execute(SendMessage(toChat, text.c_str()).replyToMessageId(messageId));
    if (!response.ok) {
        Log::Error("Could not send message: " + response.description);
    }
}

void userId(const Bot *bot, const Update *update) {
    std::string text = "ID: " + std::to_string(update->message.user.id);
    long long toChat = update->message.chat.id;
    long messageId = update->message.messageId;

    BaseResponse<Message> response = bot->execute(SendMessage(toChat, text.c_str()).replyToMessageId(messageId));
    if (!response.ok) {
        Log::Error("Could not send message: " + response.description);
    }
}

void start(const Bot *bot, const Update *update) {
    std::string text = "Hello " + update->message.user.firstName;
    long long toChat = update->message.chat.id;
    long messageId = update->message.messageId;

    BaseResponse<Message> response = bot->execute(SendMessage(toChat, text.c_str()).replyToMessageId(messageId));
    if (!response.ok) {
        Log::Error("Could not send message: " + response.description);
    }
}

void sendPoll(const Bot *bot, const Update *update) {
    long long toChat = update->message.chat.id;
    long messageId = update->message.messageId;
    BaseResponse<Message> resp = bot->execute(SendPoll(toChat, "Diocane?", std::vector{"Si", "Ah", "..."})
                                                      .replyToMessageId(messageId)
                                                      ->disableNotification()
                                                      ->disableWebPagePreview());
    if (!resp.ok) Log::Error(resp.description);
}

void sendMessage(const Bot *bot, const Update *update) {
    long long toChat = update->message.chat.id;
    long messageId = update->message.messageId;
    bot->execute(SendChatAction(toChat, Enums::ChatAction::TYPING).pointer());
    BaseResponse<Message> resp = bot->execute(SendMessage(toChat, "Test: [Google](http://www.google.it/)")
                                                      .replyToMessageId(messageId)
                                                      ->parseMode(Enums::ParseMode::MARKDOWN)
                                                      ->disableNotification()
                                                      ->disableWebPagePreview());
    if (!resp.ok) Log::Error(resp.description);
}

void sendLocation(const Bot *bot, const Update *update) {
    long long toChat = update->message.chat.id;
    long messageId = update->message.messageId;
    BaseResponse<Message> resp = bot->execute(SendLocation(toChat, 45.062828, 7.678993)
                                                      .replyToMessageId(messageId)
                                                      ->disableNotification()
                                                      ->disableWebPagePreview());
    if (!resp.ok) Log::Error(resp.description);
}

void forwardMessage(const Bot *bot, const Update *update) {
    long long fromChat = update->message.chat.id;
    long messageId = update->message.messageId;
    BaseResponse<Message> resp = bot->execute(ForwardMessage(fromChat, fromChat, messageId)
                                                      .disableNotification()
                                                      ->disableWebPagePreview());
    if (!resp.ok) Log::Error(resp.description);
}

void sendPhotoFile(const Bot *bot, const Update *update) {
    long long toChat = update->message.chat.id;
    long messageId = update->message.messageId;
    InputFile file = Utils::readInputFile("resources/test-media/Icy.jpg");
    BaseResponse<Message> resp = bot->execute(SendPhoto(toChat, &file)
                                                      .caption("Test: [Google](http://www.google.it/)")
                                                      ->replyToMessageId(messageId)
                                                      ->parseMode(Enums::ParseMode::MARKDOWN)
                                                      ->disableNotification()
                                                      ->disableWebPagePreview());
    if (!resp.ok) Log::Error(resp.description);
}

void sendAudioFile(const Bot *bot, const Update *update) {
    long long toChat = update->message.chat.id;
    long messageId = update->message.messageId;
    InputFile file = Utils::readInputFile("resources/test-media/audio.ogg");
    BaseResponse<Message> resp = bot->execute(SendAudio(toChat, &file)
                                                      .caption("Test: [Google](http://www.google.it/)")
                                                      ->replyToMessageId(messageId)
                                                      ->parseMode(Enums::ParseMode::MARKDOWN)
                                                      ->disableNotification()
                                                      ->disableWebPagePreview());
    if (!resp.ok) Log::Error(resp.description);
}

void sendVoiceFile(const Bot *bot, const Update *update) {
    long long toChat = update->message.chat.id;
    long messageId = update->message.messageId;
    InputFile file = Utils::readInputFile("resources/test-media/audio.ogg");
    BaseResponse<Message> resp = bot->execute(SendVoice(toChat, &file)
                                                      .caption("Test: [Google](http://www.google.it/)")
                                                      ->replyToMessageId(messageId)
                                                      ->parseMode(Enums::ParseMode::MARKDOWN)
                                                      ->disableNotification()
                                                      ->disableWebPagePreview());
    if (!resp.ok) Log::Error(resp.description);
}

void sendDocumentFile(const Bot *bot, const Update *update) {
    long long toChat = update->message.chat.id;
    long messageId = update->message.messageId;
    InputFile file = Utils::readInputFile("resources/test-media/uhd_test.jpg");
    BaseResponse<Message> resp = bot->execute(SendDocument(toChat, &file)
                                                      .caption("Test: [Google](http://www.google.it/)")
                                                      ->replyToMessageId(messageId)
                                                      ->parseMode(Enums::ParseMode::MARKDOWN)
                                                      ->disableNotification()
                                                      ->disableWebPagePreview());
    if (!resp.ok) Log::Error(resp.description);
}

void sendVideoFile(const Bot *bot, const Update *update) {
    long long toChat = update->message.chat.id;
    long messageId = update->message.messageId;
    InputFile file = Utils::readInputFile("resources/test-media/video.mp4");
    BaseResponse<Message> resp = bot->execute(SendVideo(toChat, &file)
                                                      .caption("Test: [Google](http://www.google.it/)")
                                                      ->replyToMessageId(messageId)
                                                      ->parseMode(Enums::ParseMode::MARKDOWN)
                                                      ->disableNotification()
                                                      ->disableWebPagePreview());
    if (!resp.ok) Log::Error(resp.description);
}

void sendVideoNoteFile(const Bot *bot, const Update *update) {
    long long toChat = update->message.chat.id;
    long messageId = update->message.messageId;
    InputFile file = Utils::readInputFile("resources/test-media/video.mp4");
    BaseResponse<Message> resp = bot->execute(SendVideoNote(toChat, &file)
                                                      .replyToMessageId(messageId)
                                                      ->disableNotification()
                                                      ->disableWebPagePreview());
    if (!resp.ok) Log::Error(resp.description);
}

void sendAnimationFile(const Bot *bot, const Update *update) {
    long long toChat = update->message.chat.id;
    long messageId = update->message.messageId;
    InputFile file = Utils::readInputFile("resources/test-media/video.mp4");
    BaseResponse<Message> resp = bot->execute(SendAnimation(toChat, &file)
                                                      .caption("Test: [Google](http://www.google.it/)")
                                                      ->replyToMessageId(messageId)
                                                      ->parseMode(Enums::ParseMode::MARKDOWN)
                                                      ->disableNotification()
                                                      ->disableWebPagePreview());
    if (!resp.ok) Log::Error(resp.description);
}

void getUserProfilePhotos(const Bot *bot, const Update *update) {
    int ofUser = update->message.user.id;
    BaseResponse<UserProfilePhotos> resp = bot->execute(GetUserProfilePhotos(ofUser).pointer());

    if (!resp.ok) Log::Error(resp.description);
    else {
        std::string message = "You have " + std::to_string(resp.result.totalCount) + " profile pictures";
        bot->execute(SendMessage(update->message.chat.id, message.c_str()).pointer());
    }
}

void getFile(const Bot *bot, const Update *update) {
    // This method is tested by getting the first user profile picture and getting its data
    int ofUser = update->message.user.id;
    BaseResponse<UserProfilePhotos> resp = bot->execute(GetUserProfilePhotos(ofUser).pointer());

    if (!resp.ok) {
        Log::Error(resp.description);
        return;
    }

    BaseResponse<File> getFileResp = bot->execute(GetFile(resp.result.photos.at(0).at(0).fileId.c_str()).pointer());
    if (!getFileResp.ok) {
        Log::Error(getFileResp.description);
        return;
    }

    std::string message;
    if (getFileResp.result.hasFilePath) {
        message = "I found the file with URL " + getFileResp.result.filePath;
    } else {
        message = "I found the file with unique ID " + getFileResp.result.fileUniqueId + " (no URL available)";
    }

    bot->execute(SendMessage(update->message.chat.id, message.c_str()).pointer());
}

void restrictChatMember(const Bot *bot, const Update *update) {
    long long inChat = update->message.chat.id;
    if (!update->message.hasReply) {
        bot->execute(SendMessage(inChat, "Quote a message").pointer());
        return;
    }
    int ofUser = update->message.replyToMessage.user.id;

    ChatPermissions perms = ChatPermissions(false, false, false, false, false, false, false, false);
    BaseResponse<bool> resp = bot->execute(RestrictChatMember(inChat, ofUser, perms).pointer());
    if (!resp.ok) Log::Error(resp.description);
}

void promoteChatMember(const Bot *bot, const Update *update) {
    long long inChat = update->message.chat.id;
    if (!update->message.hasReply) {
        bot->execute(SendMessage(inChat, "Quote a message").pointer());
        return;
    }
    int ofUser = update->message.replyToMessage.user.id;

    BaseResponse<bool> resp = bot->execute(PromoteChatMember(inChat, ofUser, true, false, false, false, true, false, true, false).pointer());
    if (!resp.ok) Log::Error(resp.description);
}

void setChatAdministratorCustomTitle(const Bot *bot, const Update *update, std::vector<std::string> args) {
    long long inChat = update->message.chat.id;
    if (args.size() < 2) {
        bot->execute(SendMessage(inChat, "Missing admin title").pointer());
        return;
    }
    if (!update->message.hasReply) {
        bot->execute(SendMessage(inChat, "Quote a message").pointer());
        return;
    }

    int ofUser = update->message.replyToMessage.user.id;

    BaseResponse<bool> resp = bot->execute(SetChatAdministratorCustomTitle(inChat, ofUser, args.at(1).c_str()).pointer());
    if (!resp.ok) Log::Error(resp.description);
}

void exportChatInviteLink(const Bot *bot, const Update *update) {
    long long toChat = update->message.chat.id;
    BaseResponse<std::string> response = bot->execute(ExportChatInviteLink(toChat).pointer());
    if (!response.ok) {
        Log::Error("Could not get chat link: " + response.description);
        return;
    }
    std::string text = "Link: " + response.result;
    bot->execute(SendMessage(toChat, text.c_str()).replyToMessageId(update->message.messageId));
}

void setChatPhoto(const Bot *bot, const Update *update) {
    long long toChat = update->message.chat.id;
    InputFile file = Utils::readInputFile("resources/test-media/Icy.jpg");
    BaseResponse<bool> response = bot->execute(SetChatPhoto(toChat, &file).pointer());
    if (!response.ok) Log::Error(response.description);
}

void deleteChatPhoto(const Bot *bot, const Update *update) {
    long long toChat = update->message.chat.id;
    BaseResponse<bool> response = bot->execute(DeleteChatPhoto(toChat).pointer());
    if (!response.ok) Log::Error(response.description);
}

void setChatTitle(const Bot *bot, const Update *update, std::vector<std::string> args) {
    long long toChat = update->message.chat.id;
    if (args.size() == 1) {
        bot->execute(SendMessage(toChat, "Missing chat title").pointer());
        return;
    }

    BaseResponse<bool> response = bot->execute(SetChatTitle(toChat, args.at(1).c_str()).pointer());
    if (!response.ok) Log::Error(response.description);
}

void setChatDescription(const Bot *bot, const Update *update, std::vector<std::string> args) {
    long long toChat = update->message.chat.id;
    if (args.size() == 1) {
        bot->execute(SendMessage(toChat, "Missing chat description").pointer());
        return;
    }

    BaseResponse<bool> response = bot->execute(SetChatDescription(toChat, args.at(1).c_str()).pointer());
    if (!response.ok) Log::Error(response.description);
}

void pinChatMessage(const Bot *bot, const Update *update) {
    long long inChat = update->message.chat.id;
    if (!update->message.hasReply) {
        bot->execute(SendMessage(inChat, "Quote a message").pointer());
        return;
    }

    int ofUser = update->message.replyToMessage.user.id;

    BaseResponse<bool> resp = bot->execute(PinChatMessage(inChat, update->message.replyToMessage.messageId).disableNotification());
    if (!resp.ok) Log::Error(resp.description);
}

void unpinChatMessage(const Bot *bot, const Update *update) {
    long long inChat = update->message.chat.id;
    BaseResponse<bool> resp = bot->execute(UnpinChatMessage(inChat).pointer());
    if (!resp.ok) Log::Error(resp.description);
}

void leaveChat(const Bot *bot, const Update *update) {
    long long inChat = update->message.chat.id;
    BaseResponse<bool> resp = bot->execute(LeaveChat(inChat).pointer());
    if (!resp.ok) Log::Error(resp.description);
}

void getChat(const Bot *bot, const Update *update) {
    long long inChat = update->message.chat.id;
    BaseResponse<Chat> resp = bot->execute(GetChat(inChat).pointer());
    if (!resp.ok) Log::Error(resp.description);
    else {
        bot->execute(SendMessage(inChat, ("Chat title is " + resp.result.title).c_str()).pointer());
    }
}

void getChatAdministrators(const Bot *bot, const Update *update) {
    long long inChat = update->message.chat.id;
    BaseResponse<std::vector<ChatMember>> resp = bot->execute(GetChatAdministrators(inChat).pointer());
    if (!resp.ok) Log::Error(resp.description);
    else {
        bot->execute(SendMessage(inChat, ("There are " + std::to_string(resp.result.size()) + " chat admins").c_str()).pointer());
    }
}

void getChatMembersCount(const Bot *bot, const Update *update) {
    long long inChat = update->message.chat.id;
    BaseResponse<int> resp = bot->execute(GetChatMembersCount(inChat).pointer());
    if (!resp.ok) Log::Error(resp.description);
    else {
        bot->execute(SendMessage(inChat, ("There are " + std::to_string(resp.result) + " chat members").c_str()).pointer());
    }
}

void getChatMember(const Bot *bot, const Update *update) {
    long long inChat = update->message.chat.id;
    int ofUser = update->message.user.id;
    BaseResponse<ChatMember> resp = bot->execute(GetChatMember(inChat, ofUser).pointer());
    if (!resp.ok) Log::Error(resp.description);
    else {
        bot->execute(SendMessage(inChat, ("You are " + resp.result.user.firstName).c_str()).pointer());
    }
}

void setChatStickerSet(const Bot *bot, const Update *update, std::vector<std::string> args) {
    long long inChat = update->message.chat.id;
    if (args.size() == 1) {
        bot->execute(SendMessage(inChat, "Missing chat description").pointer());
        return;
    }
    BaseResponse<bool> resp = bot->execute(SetChatStickerSet(inChat, args.at(1).c_str()).pointer());
    if (!resp.ok) Log::Error(resp.description);
}

void deleteChatStickerSet(const Bot *bot, const Update *update) {
    long long inChat = update->message.chat.id;
    BaseResponse<bool> resp = bot->execute(DeleteChatStickerSet(inChat).pointer());
    if (!resp.ok) Log::Error(resp.description);
}

void executeBot(const std::string& token) {
    // Create your bot!
    Bot *currentBot = new Bot(token);

    // Add the updates handler, this handler will receive every update
    currentBot->setUpdateHandler(&updateHandler);

    // Add some handlers
    currentBot->addCommandHandler("start", &start);
    currentBot->addCommandHandler("chatid", &chatId);
    currentBot->addCommandHandler("userid", &userId);
    currentBot->addCommandHandler("snd", &sendMessage);
    currentBot->addCommandHandler("fwd", &forwardMessage);
    currentBot->addCommandHandler("imgf", &sendPhotoFile);
    currentBot->addCommandHandler("audf", &sendAudioFile);
    currentBot->addCommandHandler("docf", &sendDocumentFile);
    currentBot->addCommandHandler("vidf", &sendVideoFile);
    currentBot->addCommandHandler("anif", &sendAnimationFile);
    currentBot->addCommandHandler("voif", &sendVoiceFile);
    currentBot->addCommandHandler("vdnf", &sendVideoNoteFile);
    currentBot->addCommandHandler("loc", &sendLocation);
    currentBot->addCommandHandler("poll", &sendPoll);
    currentBot->addCommandHandler("gupf", &getUserProfilePhotos);
    currentBot->addCommandHandler("getf", &getFile);
    currentBot->addCommandHandler("restr", &restrictChatMember);
    currentBot->addCommandHandler("promote", &promoteChatMember);
    currentBot->addCommandHandler("nick", &setChatAdministratorCustomTitle);
    currentBot->addCommandHandler("link", &exportChatInviteLink);
    currentBot->addCommandHandler("cpht", &setChatPhoto);
    currentBot->addCommandHandler("dpht", &deleteChatPhoto);
    currentBot->addCommandHandler("scht", &setChatTitle);
    currentBot->addCommandHandler("schd", &setChatDescription);
    currentBot->addCommandHandler("pinm", &pinChatMessage);
    currentBot->addCommandHandler("upin", &unpinChatMessage);
    currentBot->addCommandHandler("leave", &leaveChat);
    currentBot->addCommandHandler("getc", &getChat);
    currentBot->addCommandHandler("gadm", &getChatAdministrators);
    currentBot->addCommandHandler("gcmc", &getChatMembersCount);
    currentBot->addCommandHandler("gcmb", &getChatMember);
    currentBot->addCommandHandler("scss", &setChatStickerSet);
    currentBot->addCommandHandler("dcss", &deleteChatStickerSet);

    // Start polling updates
    currentBot->startPolling(true);

    /* startPolling is not blocking
       So we need to do something or the program will close
       If you don't have a blocking function to execute then just call idle() */
    currentBot->idle();
}

int main() {
    try {
        std::string token = Utils::getEnv("BOT_TOKEN");
        executeBot(token);
    } catch (Errors::RequestsException &exc) {
        Log::Error("Exception while creating bot: " + std::string(exc.what()));
        return 1;
    } catch (std::exception &exc) {
        Log::Error("Exception while creating bot: " + std::string(exc.what()));
        return 2;
    } catch (...) {
        Log::Error("Unknown fatal exception while creating bot");
        return 3;
    }
    return 0;
}
