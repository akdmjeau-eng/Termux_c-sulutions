#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_EVENTS   2048
#define MAX_CLIENTS  1024      // puedes subir a 4096–16384 en linux moderno

int set_nonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) return -1;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

int main(void) {
    int server_fd, epoll_fd;
    struct epoll_event ev, events[MAX_EVENTS];
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);

    // Crear socket servidor
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        exit(1);
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    set_nonblocking(server_fd);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(6789);

    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(server_fd, SOMAXCONN) == -1) {
        perror("listen");
        exit(1);
    }

    // Crear epoll
    epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("epoll_create1");
        exit(1);
    }

    ev.events = EPOLLIN;
    ev.data.fd = server_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &ev) == -1) {
        perror("epoll_ctl: server_fd");
        exit(1);
    }

    printf("Escuchando en :6789 ...\n");

    while (1) {
        int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            if (errno == EINTR) continue;
            perror("epoll_wait");
            break;
        }

        for (int i = 0; i < nfds; i++) {
            int fd = events[i].data.fd;

            if (fd == server_fd) {
                // Nueva conexión
                while (1) {
                    int client = accept(server_fd, (struct sockaddr*)&addr, &addrlen);
                    if (client == -1) {
                        if (errno == EAGAIN || errno == EWOULDBLOCK) break;
                        perror("accept");
                        continue;
                    }

                    set_nonblocking(client);
                    ev.events = EPOLLIN | EPOLLET;
                    ev.data.fd = client;
                    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client, &ev) == -1) {
                        perror("epoll_ctl: client");
                        close(client);
                    }
                    printf("Nueva conexión (%d)\n", client);
                }
            } else {
                // Datos en cliente existente
                char buf[4096];
                ssize_t count;

                while ((count = read(fd, buf, sizeof(buf))) > 0) {
                    // Aquí procesas los datos...
                    // Por ejemplo: eco
                    write(fd, buf, count);
                }

                if (count == 0 || (count < 0 && errno != EAGAIN)) {
                    printf("Cliente %d desconectado\n", fd);
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL);
                    close(fd);
                }
            }
        }
    }

    close(server_fd);
    close(epoll_fd);
    return 0;
}