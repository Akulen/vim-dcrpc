#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "include/discord_rpc.h"

int main(int argc, char* argv[]) {
    const char* APPLICATION_ID = "455442010573111308";

    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof(handlers));
    Discord_Initialize(APPLICATION_ID, &handlers, 1, NULL);

    char buffer[2][256];
    FILE* f;

    sleep(6);

    while(1) {
        f = fopen("/tmp/dcrpc", "r");

        DiscordRichPresence discordPresence;
        memset(&discordPresence, 0, sizeof(discordPresence));

        if(!fgets(buffer[0], sizeof(buffer[0]), f))
            exit(0);
        discordPresence.state = buffer[0];

        fgets(buffer[1], sizeof(buffer[1]), f);
        discordPresence.details = buffer[1];

        discordPresence.largeImageKey = "vim_logo";
        //discordPresence.smallImageKey = "vim_logo_s";

        discordPresence.instance = 0;
        Discord_UpdatePresence(&discordPresence);
#ifdef DISCORD_DISABLE_IO_THREAD
        Discord_UpdateConnection();
#endif
        Discord_RunCallbacks();
        sleep(5);
    }
    Discord_Shutdown();
    return 0;
}
