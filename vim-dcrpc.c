#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "include/discord_rpc.h"

const char* APPLICATION_ID = "455442010573111308";

void discordInit() {
    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof(handlers));
    Discord_Initialize(APPLICATION_ID, &handlers, 1, NULL);
}

void mainloop() {
    sleep(6);

    while(1) {
        char buffer[3][256];

        FILE* f;
        f = fopen("/tmp/dcrpc", "r");
        if(!f)
            exit(0);

        DiscordRichPresence discordPresence;
        memset(&discordPresence, 0, sizeof(discordPresence));

        if(!fgets(buffer[0], sizeof(buffer[0]), f))
            exit(0);
        discordPresence.state = buffer[0];

        fgets(buffer[1], sizeof(buffer[1]), f);
        discordPresence.details = buffer[1];

        discordPresence.largeImageKey = "vim_logo";
        discordPresence.largeImageText = "Vim > emacs";

        fgets(buffer[2], sizeof(buffer[2]), f);
        if(strcmp("ft_", buffer[2]) != 0) {
            buffer[2][strlen(buffer[2])-1] = '\0';
            discordPresence.smallImageKey = buffer[2];
            discordPresence.smallImageText = "File type";
        }

        discordPresence.instance = 0;
        Discord_UpdatePresence(&discordPresence);
#ifdef DISCORD_DISABLE_IO_THREAD
        Discord_UpdateConnection();
#endif
        Discord_RunCallbacks();

        fclose(f);
        sleep(5);
    }
}

int main() {
    discordInit();

    mainloop();

    Discord_Shutdown();
    return 0;
}
