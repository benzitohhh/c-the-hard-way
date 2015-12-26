#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512  // create a constant using the C preprocessor. It's the most reliable way of creating a constant.
#define MAX_ROWS 100

struct Address
{
    int id;
    int set; // no booleans in C, so we use an int (i.e. 1 or 0)
    char name[MAX_DATA]; // array is created within the struct
    char email[MAX_DATA];
    // i.e. so this struct is 1032 bytes
    // It is a fixed size struct - less efficient, but easier to store and read.
};

struct Database
{
    struct Address rows[MAX_ROWS];
    // Again struct contains an array (rather than a pointer to an array).
    // So again, it's a fixed size (less efficient, but we can write it to disk in one go).
    // Size here is 103,200 bytes
};

struct Connection
{
    FILE *file;
    struct Database *db;
    // This struct only holds two pointers, so it has a size of 8;
};

// forward declarations (as die uses this...)
void Database_close(struct Connection *conn);

void die(const char *message, struct Connection *conn)
{
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    Database_close(conn);
    exit(1);
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s\n",
           addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1) die("Failed to load database", conn);
}

struct Connection *Database_open(const char *filename, char mode)
{
    struct Connection *conn = malloc(sizeof(struct Connection));
    if(!conn) die("Memory error", NULL);

    conn->db = malloc(sizeof(struct Database));
    if(!conn->db) die("Memory error", conn);

    if(mode == 'c') {
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");

        if(conn->file) {
            Database_load(conn);
        }
    }

    if (!conn->file) die("Failed to open the file", conn);

    return conn;
}

void Database_close(struct Connection *conn)
{
    if (conn) {
        if (conn->file) fclose(conn->file);
        if(conn->db) free(conn->db);
        free(conn);
    }
}

void Database_write(struct Connection *conn)
{
    rewind(conn->file);

    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1) die("Failed to write database", conn);

    rc = fflush(conn->file);
    if(rc == -1) die("Cannot flush database.", conn);
}

void Database_create(struct Connection *conn)
{
    int i = 0;

    for (i = 0; i < MAX_ROWS; i++) {
        // make a prorotype to initialize it
        struct Address addr = {.id = i, .set = 0};
        // then just assign it
        conn->db->rows[i] = addr;
    }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
    struct Address *addr = &conn->db->rows[id];
    if (addr->set) die("Already set, delete it first", conn);

    addr->set = 1;

    // strncopy bug - if more than MAX_data bytes, need to explicitly set last byte to \0

    char *res = strncpy(addr->name, name, MAX_DATA);
    if (sizeof(addr->email) > MAX_DATA) {
        addr->email[MAX_DATA - 1] = '\0';
    }
    if(!res) die ("Name copy failed", conn);

    res = strncpy(addr->email, email, MAX_DATA);
    if (sizeof(addr->name) > MAX_DATA) {
        addr->name[MAX_DATA - 1] = '\0';
    }
    if (!res) die("Email copy failed", conn);
}

void Database_get(struct Connection *conn, int id)
{
    struct Address *addr = &conn->db->rows[id]; // "rows" is not a pointer, so we need to use &

    if (addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set", conn);
    }
}

void Database_delete(struct Connection *conn, int id)
{
    struct Address addr = {.id = id, .set = 0}; // temp local (stack) struct prototype
    conn->db->rows[id] = addr; // Modern C allows you to assign one struct to another, and it will handle copying over the values
}

void Database_list(struct Connection *conn)
{
    int i = 0;
    struct Database *db = conn->db;

    for (i = 0; i < MAX_ROWS; i++) {
        struct Address *cur = &db->rows[i];
        //struct Address cur2 = db->rows[i]; // This will also work... but then we are passing copy of the value to functions, rather than pointer (so we won't be able to mutate the original)

        if (cur->set) {
            //printf("cur2.name: %s\n", cur2.name);
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[])
{
    // This is how to do multiline strings in C
    char *HELP_MESSAGE =
        "Usage: ./ex17 <dbfile> <action> [action params]"
        "\n\n"
        "All options, format: <command> <human description> <action params>:\n"
        "c\tcreate db\t[max_rows, max_data]\n"
        "g\tget address\t[id]\n"
        "s\tset address\t[name, email]\n"
        "d\tdelete address\t[id]\n"
        "l\tlist addresses\t[]\n";

    if (argc < 3) die(HELP_MESSAGE, NULL);

    char *filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = Database_open(filename, action); // Also loads db into memory (unless mode is 'c', in which it gets creates in memory by database_create)
    int id = 0;

    if (argc > 3) id = atoi(argv[3]); // convert ascii string to integer
    if (id >= MAX_ROWS) die ("There's not that many records.", conn);

    switch(action) {
        case 'c':
            Database_create(conn); // just create in memory
            Database_write(conn); // but now write it to disk
            break;

        case 'g':
            if (argc != 4) die("Need an id to get", conn);

            Database_get(conn, id);
            break;

        case 's':
            if(argc != 6) die("Need id, name, email to set", conn);

            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':
            if (argc != 4) die("Need id to delete", conn);

            Database_delete(conn, id); // delete a particular row (in memory)
            Database_write(conn); // now rewrite the whole db to disk
            break;

        case 'l':
            Database_list(conn);
            break;

        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list", conn);
        }

    return 0;
}
