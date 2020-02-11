#include <string>
#include <entities/methods/GetMe.hpp>
#include <entities/Update.hpp>
#include <core/Bot.hpp>
#include <entities/methods/SendMessage.hpp>
#include <entities/methods/SendPhoto.hpp>
#include <utils/Utils.hpp>
#include <entities/methods/SendAudio.hpp>
#include <entities/methods/SendDocument.hpp>

using namespace CppTelegramBots;

void updateHandler(const Bot *bot, const Update *update) {
    Log::Debug("New update from " + update->message.user.firstName);
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

void sendMessage(const Bot *bot, const Update *update) {
    long long toChat = update->message.chat.id;
    long messageId = update->message.messageId;
    BaseResponse<Message> resp = bot->execute(SendMessage(toChat, "Test: [Google](http://www.google.it/)")
                                                      .replyToMessageId(messageId)
                                                      ->parseMode(Enums::ParseMode::MARKDOWN)
                                                      ->disableNotification()
                                                      ->disableWebPagePreview());
    if (!resp.ok) Log::Error(resp.description);
}

void sendPhotoFile(const Bot *bot, const Update *update) {
    long long toChat = update->message.chat.id;
    long messageId = update->message.messageId;
    std::string imageData = Utils::readFullFile("resources/images/uhd_test.jpg");
    BaseResponse<Message> resp = bot->execute(SendPhoto(toChat, InputFile("uhd_test.jpg", &imageData))
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
    std::string imageData = Utils::readFullFile("resources/audios/audio.ogg");
    BaseResponse<Message> resp = bot->execute(SendAudio(toChat, InputFile("audio.ogg", &imageData))
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
    std::string imageData = Utils::readFullFile("resources/images/uhd_test.jpg");
    BaseResponse<Message> resp = bot->execute(SendDocument(toChat, InputFile("uhd_test.jpg", &imageData))
                                                      .caption("Test: [Google](http://www.google.it/)")
                                                      ->replyToMessageId(messageId)
                                                      ->parseMode(Enums::ParseMode::MARKDOWN)
                                                      ->disableNotification()
                                                      ->disableWebPagePreview());
    if (!resp.ok) Log::Error(resp.description);
}

void executeBot(const std::string& token) {
    // Create your bot!
    Bot *currentBot = new Bot(token);

    // Add the updates handler, this handler will receive every update
    currentBot->setUpdateHandler(&updateHandler);

    // Add some handlers
    currentBot->addCommandHandler("start", &start);
    currentBot->addCommandHandler("snd", &sendMessage);
    currentBot->addCommandHandler("imgf", &sendPhotoFile);
    currentBot->addCommandHandler("audf", &sendAudioFile);
    currentBot->addCommandHandler("docf", &sendDocumentFile);

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