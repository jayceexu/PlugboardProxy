// Plugboard Proxy for encryption, to reinforce the security of
// mutual connection (e.g. ssh).
//
// Copyright: Jian Xu(jianxu1@cs.stonybrook.edu)
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "stdbool.h"
#include "proxy_server.h"
#include "proxy_client.h"
#include "log.h"

extern char * optarg;
static const int ARG_LEN = 256;

int main(int argc, char *argv[])
{
    if (argc < 5) {
        printf ("Invalid argument!"
                " pbproxy [-l port] -k keyfile destination port\n");
        return -1;            
    }
    bool has_key = false;
    bool server_mode = false;  // By default, it will be in client-mode
    int op = 0;
    int listen_port = 0;
    char mykey[ARG_LEN];
    while ((op = getopt(argc, argv, "l:k:")) != -1) {
        switch (op) {
        case 'l':
            listen_port = atoi(optarg);
            DEBUG_LOG ("the listen port is %d", listen_port);
            server_mode = true;
            break;
        case 'k':
            strncpy(mykey, optarg, ARG_LEN);
            DEBUG_LOG ("key is %s", mykey);
            has_key = true;
            break;
        default:
            DEBUG_LOG ("Invalid argument!"
                    " pbproxy [-l port] -k keyfile destination port");
            return -1;            
        }

    }
    if (!has_key) {
        DEBUG_LOG ("Should indicate encryption file");
        return -1;
    }

    int arg_i = optind;
    const char * proxy_addr = argv[arg_i];
    int proxy_port = atoi(argv[arg_i+1]);
    DEBUG_LOG ("proxy address %s", proxy_addr);
    DEBUG_LOG ("proxy port %d", proxy_port);

    if (server_mode) {
        start_proxy_server(mykey, proxy_addr, proxy_port, listen_port);
    } else {
        start_proxy_client(mykey, proxy_addr, proxy_port);
    }

    return 0;
}


