#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "include/discord_rpc.h"

const char* APPLICATION_ID = "455442010573111308";

void discordInit() {
    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof(handlers));
    Discord_Initialize(APPLICATION_ID, &handlers, 1, NULL);
}

void mainloop() {
    time_t start = time(0);
    while(!sleep(5)) {
        char buffer[2][256];

        FILE* f;
        f = fopen("/tmp/dcrpc", "r");
        if(!f)
            return;

        DiscordRichPresence discordPresence;
        memset(&discordPresence, 0, sizeof(discordPresence));

        if(!fgets(buffer[0], sizeof(buffer[0]), f))
            continue;
        discordPresence.state = buffer[0];

        fgets(buffer[1], sizeof(buffer[1]), f);
        discordPresence.details = buffer[1];

        discordPresence.largeImageKey = "vim_logo";
        discordPresence.largeImageText = "Vim > emacs";

        discordPresence.startTimestamp = start;

        Discord_UpdatePresence(&discordPresence);
#ifdef DISCORD_DISABLE_IO_THREAD
        Discord_UpdateConnection();
#endif
        Discord_RunCallbacks();

        fclose(f);
    }
}

int main() {
    discordInit();

    mainloop();

    Discord_Shutdown();
    return 0;
}
