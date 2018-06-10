#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "include/discord_rpc.h"

const char* APPLICATION_ID = "455442010573111308";
int SendPresence = 1;

static void updateDiscordPresence(int linenum, int curline, char* filename) {
    if (SendPresence) {
        char buffer[2][256];
        DiscordRichPresence discordPresence;
        memset(&discordPresence, 0, sizeof(discordPresence));
        sprintf(buffer[0], "Line: %d of %d", curline, linenum);
        discordPresence.state = buffer[0];
        sprintf(buffer[1], "Editing %s", filename);
        discordPresence.details = buffer[1];
        discordPresence.largeImageKey = "vim_logo";
        //discordPresence.smallImageKey = "vim_logo_s";
        discordPresence.instance = 0;
        Discord_UpdatePresence(&discordPresence);
    }
    else {
        Discord_ClearPresence();
    }
}

static void handleDiscordReady(const DiscordUser* connectedUser) {
    printf("\nDiscord: connected to user %s#%s - %s\n",
           connectedUser->username,
           connectedUser->discriminator,
           connectedUser->userId);
}

static void handleDiscordDisconnected(int errcode, const char* message) {
    printf("\nDiscord: disconnected (%d: %s)\n", errcode, message);
}

static void handleDiscordError(int errcode, const char* message) {
    printf("\nDiscord: error (%d: %s)\n", errcode, message);
}

static void discordInit() {
    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof(handlers));
    handlers.ready = handleDiscordReady;
    handlers.disconnected = handleDiscordDisconnected;
    handlers.errored = handleDiscordError;
    Discord_Initialize(APPLICATION_ID, &handlers, 1, NULL);
}

static void mainloop() {
    char buffer[512];
    FILE* f;

    int linenum, curline;
    char* filename = malloc(512 * sizeof(*filename));

    sleep(6);

    while(1) {
        f = fopen("/tmp/dcrpc", "r");
        if(!fgets(buffer, sizeof(buffer), f))
            exit(0);
        strcpy(filename, buffer);
        fgets(buffer, sizeof(buffer), f);
        curline = atoi(buffer);
        fgets(buffer, sizeof(buffer), f);
        linenum = atoi(buffer);
        updateDiscordPresence(linenum, curline, filename);

#ifdef DISCORD_DISABLE_IO_THREAD
        Discord_UpdateConnection();
#endif
        Discord_RunCallbacks();
        sleep(5);
    }
}

int main(int argc, char* argv[]) {
    discordInit();

    mainloop();

    Discord_Shutdown();
    return 0;
}
