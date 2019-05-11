#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

struct Address {
    int id;
    int set;
    char name[MAX_DATA];
    char email[MAX_DATA];
};

struct Database {
    struct Address rows[MAX_ROWS];
};

struct Connection {
    FILE *file;
    struct Database *db;
};

void die(const char *message) {
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

void Address_print(struct Address *address) {
    printf("%d %s %s\n", address->id, address->name, address->email);
}

void Database_load(struct Connection *conn) {
    int result = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if (result != 1) {
        die("Failed to load database");
    }
}

struct Connection *Connection_open(const char *filename, char mode) {
    struct Connection *conn = malloc(sizeof(struct Connection));

    if (!conn) {
        die("Memory error while opening database connection");
    }

    conn->db = malloc(sizeof(struct Database));
    if (!conn->db) {
        die("Memory error while creating database");
    }

    if ('c' == mode) {
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");

        if (conn->file) {
             Database_load(conn);
        }
    }

    if (!conn->file) {
        die("Failed to open to database file");
    }

    return conn;
}

void Connection_close(struct Connection *conn) {
    if (conn) {
        if (conn->file) {
            fclose(conn->file);
        }
        if (conn->db) {
            free(conn->db);
        }
        free(conn);
    }
}

void Database_create(struct Connection *conn) {
    int i = 0;

    for (i = 0; i < MAX_ROWS; i++) {
        // make a prototype to initialize it
        struct Address addr = {.id = i, .set = 0 };
        // then just assign it
        conn->db->rows[i] = addr;
    }
}

void Database_write(struct Connection *conn) {
    rewind(conn->file);

    int result = fwrite(conn->db, sizeof(struct Database), 1, conn->file);

    if (result != 1) {
        die("Failed to write database");
    }

    result = fflush(conn->file);
    if (result == -1) {
        die("Cannot flush database");
    }
}

void Database_list(struct Connection *conn) {
    int i = 0;
    struct Database *db = conn->db;

    for (i = 0; i < MAX_ROWS; i++) {
        struct Address *cur = &db->rows[i];

        if (cur->set) {
            Address_print(cur);
        }
    }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email) {
    struct Address *addr = &conn->db->rows[id];
    if (addr->set) {
        die("Already set, delete it first");
    }

    addr->set = 1;

    // WARNING: bug here
    char *res = strncpy(addr->name, name, MAX_DATA - 1);
    //demonstrate the bug
    if (!res) {
        die("Name copy failed");
    }

    res = strncpy(addr->email, email, MAX_DATA - 1);
    if (!res) {
        die("Email copy failed");
    }
    printf("Set data in row %d to:\n", id);
    Address_print(&conn->db->rows[id]);
}

void Database_get(struct Connection *conn, int id) {
    struct Address *addr = &conn->db->rows[id];

    if (addr->set) {
        Address_print(addr);
    } else {
        die("Address at given id not set");
    }
}

void Database_delete(struct Connection *conn, int id) {
    struct Address addr = {.id = id,.set = 0 };
    conn->db->rows[id] = addr;
}

int main(int argc, char *argv[]) {

    if (argc < 3) {
        die("USAGE: ex17 <dbfile> <action> [action params]\nExample: ex17 test.db c");
    }

    char *filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = Connection_open(filename, action);

    int id = 0;
    if (argc > 3) id = atoi(argv[3]);
    if (id >= MAX_ROWS) die("id too large");

    switch(action) {
        // Create empty database
        case 'c':
            Database_create(conn);
            Database_write(conn);
            break;

        // Get an address by id
        case 'g':
            if (argc != 4) {
                die("Need to provide an id to get");
            }

            Database_get(conn, id);
            break;

        // Set an address
        case 's':
            if (argc != 6) {
                die("Need to provide id, name and email to set an Address");
            }
            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        // Delete an address
        case 'd':
            if (argc != 4) {
                die("Need to provide an id to delete");
            }

            Database_delete(conn, id);
            Database_write(conn);
            break;

        // List the contents of the database
        case 'l':
            Database_list(conn);
            break;

        default:
            die("Invalid option. Valid: c=create, g=get, s=set, d=del, l=list");
    }

    Connection_close(conn);
    

    return 0;
}
